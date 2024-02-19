public class FileSys {
    static {
        System.loadLibrary("FileSys");
    }

    private final String root;
    private final boolean allowHidden;

    public FileSys() {
        this(null, false);
    }

    public FileSys(String root) {
        this(root, false);
    }

    public FileSys(boolean allowHidden) {
        this(null, allowHidden);
    }

    public FileSys(String root, boolean allowHidden) {
        this.root = root;
        this.allowHidden = allowHidden;
    }

    public void printFiles() {
        printFiles(false);
    }

    public native void printFiles(boolean recursive);
}
