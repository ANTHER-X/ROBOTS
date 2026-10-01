#ifndef SOUNDSYSTEM_HPP
#define SOUNDSYSTEM_HPP

#include <Arduino.h>
#include <Dependencias/Sensores.hpp>
#include <Config.hpp>

class SoundSystem{
protected:

    // Tipo de buzzer por defecto
    BuzzerType buzzerType;
    // Notas
    const Nota* const* Notas[MAXSOUNDS];
    uint8_t INotesCount[MAXSOUNDS] = {0}; // Contador de nota actual de Musica
    uint8_t ISoundCount = 0; // Que cancion se esta reproduciendo actualmente
    uint8_t NotesSize[MAXSOUNDS] = {0}; // Size de cada cancion
    uint8_t SoundSize = 0; // Cantidad de canciones actuales
    bool NotesActive[MAXSOUNDS] = {0}; // Si una cancion esta activa

    // Donde estan las Notas.    True = RAM. False = Flash
    NotesStorage notesStorage;
    // Duracion actual de Nota. en MS
    unsigned long ActualNoteEndPlayTime = 0; // El tiempo donde la nota el reproduccion termina
    // En caso de pausar, nos indica el tiempo que faltaba en la reproduccion de esa melodia.
    uint16_t FaltanteStopNoteDuration = 0;
    // pin de buzzer
    uint8_t BuzzerPin;

    // Funciones
    inline void EnableDisableMusic(uint8_t index, bool active){
        if(index > SoundSize) return;
        NotesActive[index] = active;
    }

    // Reproducir las melodias
    void PlayMusic(uint8_t soundIndex);
public:
    SoundSystem(NotesStorage storageNotesType = NotesStorage::NOTES_RAM, BuzzerType buzzerType = BuzzerType::BUZZER_ACTIVE);

    void AddBuzzerPin(uint8_t pin);
    void AddMusic(const Nota* const* Music, uint8_t MusicSize, bool active = true);
    uint8_t GetIndexMusic(const Nota* const* Music);

    inline void EnableMusic(uint8_t index){ EnableDisableMusic(index, true);}
    inline void DisableMusic(uint8_t index){ EnableDisableMusic(index, false);}

    void ResetSounds(bool All_AllNoActual = true); // Reinicio de indice de melodias

    void Play(uint8_t indexSound); // Reproduces la melodia que quieras
    void Play(){Play(ISoundCount); } // Reproduccion automatica
    void Stop(); // Pausa musica
};


#endif //SOUNDSYSTEM_HPP