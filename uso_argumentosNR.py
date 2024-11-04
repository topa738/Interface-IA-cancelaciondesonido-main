import numpy as np
import pyaudio
import webrtcvad
import tensorflow as tf
import time
import noisereduce as nr
import argparse
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

p = pyaudio.PyAudio()

# Mostrar los dispositivos de audio disponibles
for i in range(p.get_device_count()):
    info = p.get_device_info_by_index(i)
    print(f"Device {i}: {info['name']}")

# Inicializar stream de captura
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
            if IA_ACTIVA:
                # Convertir el buffer de audio a un array NumPy
                audio_data_np = np.frombuffer(audio_data, dtype=np.int16)

                # Aplicar reducción de ruido
                reduced_noise = nr.reduce_noise(y=audio_data_np, sr=RATE)

                # Convertir el array reducido a bytes para el stream de salida
                denoised_audio_bytes = reduced_noise.astype(np.int16).tobytes()
                output_stream.write(denoised_audio_bytes)
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
