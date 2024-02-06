public class EjemploT {
    public static void main(String[] args) {

        HiloThread hiloThread = new HiloThread();
        //utilizamos el método .start() para iniciar el hilo y se ejecute de forma concurrente
        hiloThread.start();
    }
}


// Clase que extiende la clase Thread
class HiloThread extends Thread {
    @Override
    public void run() {
        for (int i = 0; i < 100; i++) {
            System.out.println("[Thread] = Celeste Batres");
        }
    }
}
