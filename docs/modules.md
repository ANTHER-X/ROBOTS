# Modules

Dentro de la carpeta `modules` encontrarás varias clases, estructuras y/o funciones que son complementarias para los robots. Estas no necesariamente son completamente necesarias, sino que pueden ser un complemento para los robots o una adición de funcionalidades.

## SoundSystem

| Método | Descripción |
|--------|-------------|
| `SoundSystem` | Pide dónde se guardarán las notas, **RAM** o **Flash** (por defecto, **RAM**), y el tipo de buzzer, **Activo** o **Pasivo** (por defecto, **Activo**). |
| `AddBuzzerPin` | Pide el pin del buzzer e internamente lo inicializa. |
| `AddMusic` | Agrega una melodía a la lista. Pide tanto el array de la melodía como su tamaño (`size`), así como si la canción está o no activa para reproducción. |
| `GetIndexMusic` | Devuelve el índice interno de una melodía en la lista. Si la melodía ingresada no existe en la lista, regresa el índice `0` como valor por defecto: si no hay ninguna melodía agregada, no se reproducirá nada; si hay al menos una, se tomará la primera melodía agregada como la melodía por defecto. |
| `EnableMusic` | Habilita una melodía para reproducción; pide el índice interno de la melodía. |
| `DisableMusic` | Deshabilita la reproducción de una melodía; pide el índice interno de la melodía. |
| `ResetSounds` | Reinicia el índice de reproducción de las melodías para que se reproduzcan desde cero. Pide un `bool`: **True** si todas las melodías serán reiniciadas, **False** para excluir a la melodía en reproducción. |
| `Play` | Reproduce una melodía. Puedes, opcionalmente, pasar el índice de la que quieres reproducir; si no pasas nada, la reproducción por defecto es lineal, conforme se agregaron. |
| `Stop` | Detiene cualquier melodía que esté en reproducción. | 