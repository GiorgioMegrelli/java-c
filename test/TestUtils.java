public class TestUtils {
    private static boolean doPrintRule = false;

    public static void doPrint(boolean rule) {
        TestUtils.doPrintRule = rule;
    }

    public static boolean doPrint() {
        return TestUtils.doPrintRule;
    }

    public static void println(String data) {
        if(doPrintRule) {
            System.out.println(data);
        }
    }

    public static void assertContains(String data, String subStr) {
        if(!(data != null && subStr != null && data.contains(subStr))) {
            throw new RuntimeException("Test Failed");
        }
    }

    public static void assertContains(String data, String... subStrs) {
        for(String s: subStrs) {
            assertContains(data, s);
        }
    }
}
