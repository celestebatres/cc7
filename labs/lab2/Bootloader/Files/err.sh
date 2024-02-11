bochs_pid=$(pgrep bochs)

# Verificar si se encontró el proceso
if [ -z "$bochs_pid" ]; then
    echo "No se encontró el proceso bochs."
else
    # Matar el proceso bochs
    echo "Matando el proceso bochs (PID: $bochs_pid)..."
    kill -9 "$bochs_pid"
    echo "Proceso bochs terminado exitosamente."
fi

rm ./obj/boot/bochs.img.lock