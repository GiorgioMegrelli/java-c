public class FileSys {
    static {
        System.loadLibrary("FileSys");
    }

    public void printFiles() {
        printFiles(false);
    }

    public native void printFiles(boolean recursive);
}
