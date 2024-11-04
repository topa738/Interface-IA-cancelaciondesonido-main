import numpy as np
import pyaudio
import webrtcvad
import tensorflow as tf
import sys
from tensorflow.keras.models import load_model


TAMANIO_BUFFER = 320  # Aumentar el tamaño del búfer
RATE = 32000  # Frecuencia de muestreo
PARAMETROVAD = int(sys.argv[1])
DISPOSITIVO_ENTRADA = int(sys.argv[2])
DISPOSITIVO_SALIDA = int(sys.argv[3])
IA_ACTIVA = bool(sys.argv[4])
WEBRTCVAD_ACTIVA = bool(sys.argv[5])

print(PARAMETROVAD,DISPOSITIVO_ENTRADA,DISPOSITIVO_SALIDA,IA_ACTIVA, WEBRTCVAD_ACTIVA)

vad = webrtcvad.Vad(PARAMETROVAD)
# Cargar tu modelo de IA preentrenado
model_path = '/home/facu/Escritorio/repos/IA-cancelacion-de-ruido-/wave_u_net_model320441002.keras'
print("Cargando modelo guardado...")
model = load_model(model_path)
print("Modelo cargado exitosamente.")

def calcular_decibelios(buffer):
    rms = np.sqrt(np.mean(np.square(buffer)))
    return 20 * np.log10(rms) if rms > 0 else -100

@tf.function(jit_compile=True)
def procesar_audio(audio_data):
    # Convertir el array de NumPy a un tensor de TensorFlow
    audio_data_tf = tf.convert_to_tensor(audio_data, dtype=tf.int16)



    # Expandir dimensiones para que coincida con la entrada del modelo
    audio_data_tf = tf.expand_dims(audio_data_tf, axis=0)  # Añadir dimensión de batch
    audio_data_tf = tf.expand_dims(audio_data_tf, axis=-1)  # Añadir dimensión de canal

    # Procesar audio utilizando el modelo con XLA
    return model(audio_data_tf)

# Configurar PyAudio
p = pyaudio.PyAudio()

# Mostrar los dispositivos de audio disponibles
for i in range(p.get_device_count()):
    info = p.get_device_info_by_index(i)
    print(f"Device {i}: {info['name']}")

# Inicializar stream de captura
stream = p.open(format=pyaudio.paInt16,
                channels=1,
                rate=44100,
                input=True,
                 frames_per_buffer=TAMANIO_BUFFER,
                input_device_index=DISPOSITIVO_ENTRADA
                )

# Inicializar stream de salida para el micrófono virtual
output_stream = p.open(format=pyaudio.paInt16,
                       channels=1,
                       rate=44100,
                       output=True,
                       frames_per_buffer=TAMANIO_BUFFER,
                       output_device_index=DISPOSITIVO_SALIDA)


print("Iniciando la captura y filtrado de audio...")
pasos = 0

try:
    while True:
        # Leer audio del micrófono
        audio_data = stream.read(TAMANIO_BUFFER)
        if(WEBRTCVAD_ACTIVA):
            is_active = vad.is_speech(audio_data, sample_rate=RATE)
        else:
            is_active=True
        if pasos > 10:
            if(is_active):
                if IA_ACTIVA:
                    audio_data_np = np.frombuffer(audio_data, dtype=np.int16)
                    denoised_audio = procesar_audio(audio_data_np)
                    denoised_audio_bytes = denoised_audio.numpy().astype(np.int16).tobytes()
                    output_stream.write(denoised_audio_bytes)
                else:
                    output_stream.write(audio_data)
                    # Enviar el audio procesado al micrófono virtual
        else:
            pasos += 1

except KeyboardInterrupt:
    print("Deteniendo la captura de audio...")

finally:
    # Cerrar streams y PyAudio
    stream.stop_stream()
    stream.close()
    output_stream.stop_stream()
    output_stream.close()
    p.terminate()
