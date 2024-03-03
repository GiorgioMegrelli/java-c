import static java.lang.String.format;

public class Main {
    private static String runPrintFiles(String root, boolean allowHidden) {
        return runPrintFiles(root, allowHidden, null);
    }

    private static String runPrintFiles(
        String root, boolean allowHidden, Boolean recursive
    ) {
        TestUtils.println(format(
            "new FileSys(\"%s\", %b).printFiles(%s);",
            root, allowHidden, (recursive == null)? "": recursive
        ));
        FileSys fileSys = new FileSys("", allowHidden);
        String content = (recursive == null)? fileSys.printFiles(): fileSys.printFiles(recursive);
        TestUtils.println(content);
        return content;
    }

    public static void main(String[] args) {
        TestUtils.doPrint(true);
        TestUtils.assertContains(
            runPrintFiles(".", false, false),
            "README.md", "build.sh", "clean.sh"
        );
    }
}
