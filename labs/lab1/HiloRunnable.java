class HiloRunnable implements Runnable {
    public void run() {
        for (int i = 0; i < 100; i++) {
            System.out.println("HiloRunnable No." + i);
        }
    }

    public static void main(String[] args) {
        HiloRunnable hiloRunnable = new HiloRunnable();
        Thread hilo = new Thread(hiloRunnable);
        hilo.start();
    }
}