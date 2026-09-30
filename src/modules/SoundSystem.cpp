#include <modules/SoundSystem.hpp>

SoundSystem::SoundSystem(NotesStorage storageNotesType, BuzzerType buzzerType){
    this->buzzerType = buzzerType;
    this->notesStorage = storageNotesType;
}

void SoundSystem::AddBuzzerPin(uint8_t pin){
    this->BuzzerPin = pin;
    pinMode(BuzzerPin, OUTPUT);
}


void SoundSystem::AddMusic(const SoundNote* const* Music, uint8_t MusicSize, bool active){
    if(SoundSize > MAXSOUNDS){
        DBG_PRINTLN("Cantidad no valida de notas!");
        return;
    }

    // Agreamos la cancion de acuerdo en donde esta
    Notas[SoundSize] = Music;
    
    // Damos los datos
    NotesSize[SoundSize] = MusicSize;
    NotesActive[SoundSize] = active;

    SoundSize++;
    DBG_PRINTLN("Se ah agregado la musica al sistema");
}

uint8_t SoundSystem::GetIndexMusic(const SoundNote* const* Music){

    for(int8_t i=0; i<SoundSize; i++)
        if(Notas[i] == Music) return i; // Retornamos la que coincida

    return 0; // Por defecto la primera, si no hay melodias no se reproducira nada.
}

void SoundSystem::ResetSounds(bool All_AllNoActual){
    // Guardamos indice actual de reproduccion de melodia actual
    uint8_t auxActualCount = INotesCount[ISoundCount];
    // Reiniciamos indices
    for(uint8_t i=0; i<SoundSize; i++)
        INotesCount[i] = 0;
    // Si no quiere reiniciar la melodia actual
    if(!All_AllNoActual) INotesCount[ISoundCount] = auxActualCount;
}


void SoundSystem::PlayMusic(uint8_t soundIndex){
    // Index invalido
    if(soundIndex >= SoundSize){
        DBG_PRINTLN("Melodia inexistente!!!");
        return;
    }

    // Nota termina, restamos para validar si se termino la nota, casteamos a signed para evitar
    // desbordamientos
    if( (uint32_t)((millis() - ActualNoteEndPlayTime)) < 1) return;
    else DBG_PRINTLN("Nota terminada, Reproduciendo la siguiente...");

    // Si se termino la melodia regresamos a la primer nota y pausamos
    if(INotesCount[soundIndex] >= NotesSize[soundIndex]){
        ISoundCount = soundIndex;
        // Pausamos segun el tipo de buzzer
        if(buzzerType == BuzzerType::BUZZER_PASSIVE) noTone(BuzzerPin);
        else if(buzzerType == BuzzerType::BUZZER_ACTIVE) digitalWrite(BuzzerPin, LOW);
        
        INotesCount[soundIndex] = 0;
        DBG_VALUE_LN("Melodia Terminada, index returna a: ", INotesCount[soundIndex]);
        DBG_PRINTLN("Todas las melodias han sido reproducidas, reiniciando...");

        if(ISoundCount < SoundSize-1) ISoundCount = soundIndex+1; // Ponemos la melodia siguiente a la que agrego
        else ISoundCount = 0;
        DBG_VALUE_LN("Siguiente melodia en reproduccion: ", ISoundCount);

        return;
    }

    // Dependiendo donde esta la nota, la sacamos
    const SoundNote* const* Lista = Notas[soundIndex];
    const SoundNote* nota;
    // Tomamos la nota
    if(notesStorage == NotesStorage::NOTES_FLASH){
        nota = (const SoundNote*)pgm_read_ptr(&Lista[INotesCount[soundIndex]]);
        DBG_PRINTLN("Nota Tomada desde Flash.");
    }else{
        nota = Lista[INotesCount[soundIndex]];
        DBG_PRINTLN("Nota Tomada desde RAM.");
    }

    // Reproducimos la nota
    // En Buzzer Pasivo
    if(nota->frecuencia > 0 && buzzerType == BUZZER_PASSIVE){ // Hay sonido
        tone(BuzzerPin, nota->frecuencia);
        DBG_PRINTLN("Buzzer Pasivo: Nota En reproduccion");
    }
    else if(nota->frecuencia <= 0 && buzzerType == BUZZER_PASSIVE){ // No hay sonido
        noTone(BuzzerPin);
        DBG_PRINTLN("Buzzer Pasivo: Silencio");
    }
    // Buzzer Activo
    else{
        digitalWrite(BuzzerPin, (nota->frecuencia > 0));
        DBG_PRINTLN("Buzzer Activo: nota En reproduccion");
    }
    
    //Aumentamos para la siguiente nota y tomamos el tiempo actual
    actualNotaTime = millis();
                                                              // Si la reproduccion se pauso y la melodia no es la misma que la anterior
    ActualNoteEndPlayTime = actualNotaTime + nota->duracion - ((soundIndex != ISoundCount) ? (RetardoStopNoteDuration) : (0));
    RetardoStopNoteDuration = 0; // Ya que se uso  el retardo, lo eliminamos.
    // Decimos que la melodia en reproduccion es la del indice.
    ISoundCount = soundIndex;

    DBG_VALUE_LN("El index de de la melodia es: ", ISoundCount);
    DBG_VALUE_LN("El index de la nota tocada es: ", INotesCount[ISoundCount]);

    // Actualizamos el indice de melodia siguiente
    if(INotesCount[ISoundCount] < NotesSize[ISoundCount]) INotesCount[ISoundCount]++;
    else INotesCount[ISoundCount] = 0;
}

void SoundSystem::Play(uint8_t indexSound){
    if(SoundSize == 0){
        DBG_PRINTLN("No hay melodias... No se reproduce nada");
        return;
    }
    PlayMusic(indexSound);
}

void SoundSystem::Stop(){
    // Cancelamos sonido.
    if(buzzerType == BUZZER_PASSIVE){
        noTone(BuzzerPin);
        DBG_PRINTLN("Buzzer Pasivo: Pausado");
    }
    else{
        digitalWrite(BuzzerPin, 0);
        DBG_PRINTLN("Buzzer Activo: Pausado");
    }

    // Decimos cuanto tiempo faltaba para que la nota terminara
    RetardoStopNoteDuration = (millis() - ActualNoteEndPlayTime);
    ActualNoteEndPlayTime = millis();
}