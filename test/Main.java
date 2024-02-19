public class Main {
    public static void main(String[] args) {
        FileSys fileSys = new FileSys(".");

        System.out.println("printFiles(true):");
        fileSys.printFiles(true);
        System.out.println();

        System.out.println("printFiles(false):");
        fileSys.printFiles(false);
        System.out.println();
    }
}
