#include <modules/SoundSystem.hpp>

SoundSystem::SoundSystem(NotesStorage storageNotesType, BuzzerType buzzerType){
    this->buzzerType = buzzerType;
    this->notesStorage = storageNotesType;
}

void SoundSystem::AddBuzzerPin(uint8_t pin){
    this->BuzzerPin = pin;
    pinMode(BuzzerPin, OUTPUT);
}


void SoundSystem::AddMusic(const Nota* const* Music, uint8_t MusicSize, bool active){
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

uint8_t SoundSystem::GetIndexMusic(const Nota* const* Music){

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
    // Index invalido o Melodia inactiva
    if(soundIndex >= SoundSize || NotesActive[soundIndex] == false){
        DBG_PRINTLN("Melodia inexistente!!!");
        Stop();
        return;
    }
    
    // Tomamos una lectura de millis() para la funcion
    const uint32_t now = millis();

    // Nota termina, restamos para validar si se termino la nota, casteamos a signed para evitar
    // desbordamientos. Y vemos si es que hubo una pausa
    if( (int32_t)((now - ActualNoteEndPlayTime)) < 0) return;
    else DBG_PRINTLN("Nota terminada, Reproduciendo la siguiente...");

    // Tomamos datos para ver si reanudamos la nota anterior si hubo pausa
    const bool mismaMelodia = (soundIndex == ISoundCount);
    // Si no era la misma melodia descartamos el retraso
    if(!mismaMelodia) FaltanteStopNoteDuration = 0;
    // Vemos si se necesira reanudar la melodia
    const bool reanuda = mismaMelodia && FaltanteStopNoteDuration > 0;

    // Si se termino la melodia y no necesitamos reanudar
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

    // Si reanudamos la nota faltante de terminar era la anterior ya que al final aumentamos
    const uint8_t idNotaActual = (reanuda ? (INotesCount[soundIndex] - 1) : INotesCount[soundIndex]);

    // Dependiendo donde esta la nota, la sacamos
    const Nota* const* Lista = Notas[soundIndex];
    Nota nota;   // copia local en RAM
    if(notesStorage == NotesStorage::NOTES_FLASH){
        const Nota* notaPtr = (const Nota*)pgm_read_ptr(&Lista[idNotaActual]);
        memcpy_P(&nota, notaPtr, sizeof(Nota));
        DBG_PRINTLN("Nota Tomada desde Flash.");
    }else{
        nota = *Lista[idNotaActual];
        DBG_PRINTLN("Nota Tomada desde RAM.");
    }

    // Tomamos el tiempo de la duracion de la nota de acuerdo a si se reanudo o no
    const uint32_t durationNota = (reanuda ? (FaltanteStopNoteDuration) : (nota.duracion));
    FaltanteStopNoteDuration = 0;

    // Reproducimos la nota
    // En Buzzer Pasivo
    if(nota.frecuencia > 0 && buzzerType == BUZZER_PASSIVE){ // Hay sonido
        tone(BuzzerPin, nota.frecuencia);
        DBG_PRINTLN("Buzzer Pasivo: Nota En reproduccion");
    }
    else if(nota.frecuencia <= 0 && buzzerType == BUZZER_PASSIVE){ // No hay sonido
        noTone(BuzzerPin);
        DBG_PRINTLN("Buzzer Pasivo: Silencio");
    }
    // Buzzer Activo
    else{
        digitalWrite(BuzzerPin, (nota.frecuencia > 0));
        DBG_PRINTLN("Buzzer Activo: nota En reproduccion");
    }

    // El tiempo final lo tomamos en caso de que haya algun retraso o de que se haya necesitado
    // reanudar
    if(reanuda || !mismaMelodia || (int32_t)(now - ActualNoteEndPlayTime) >= (int32_t)durationNota)
        ActualNoteEndPlayTime = now + durationNota;
    // Lo tomamos asi solo si la reproduccion salio perfecta sin desvios de tiempo
    else
        ActualNoteEndPlayTime += durationNota;

    // Melodia actual que se esta reproduciendo
    ISoundCount = soundIndex;

    DBG_VALUE_LN("El index de de la melodia es: ", ISoundCount);
    DBG_VALUE_LN("El index de la nota tocada es: ", idNotaActual);

    // Seguimos con la siguiente en caso de que no se haya reanudado la nota.
    // Si se ranudo, esta nota es la que sigue. asi que no aumentariamos
    if(!reanuda) INotesCount[soundIndex]++;
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
    uint32_t now = millis();
    int32_t restante = (int32_t)(ActualNoteEndPlayTime - now);
    if(restante > 0) FaltanteStopNoteDuration = (uint32_t)restante;
    ActualNoteEndPlayTime = now;
}