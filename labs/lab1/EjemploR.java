public class EjemploR {
    public static void main(String[] args) {
        HiloRunnable hiloRunnable = new HiloRunnable();

        // Crear una instancia de la clase Thread pasando el objeto Runnable como argumento
        Thread hiloThread = new Thread(hiloRunnable);

        // Utilizamos .start() para iniciar el hilo y se ejecute de forma concurrente
        hiloThread.start();

    }
}

// Clase que implementa la interfaz Runnable
class HiloRunnable implements Runnable {
    @Override
    public void run() {
        for (int i = 0; i < 100; i++) {
            System.out.println("[Runnable] = Celeste Batres");
        }
    }
}