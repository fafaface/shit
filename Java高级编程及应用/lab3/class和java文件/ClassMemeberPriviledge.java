
import java.util.HashSet;

public class ClassMemeberPriviledge {
    public static void main(String[] args) {
        if (!check(args)) {
            return;
        }
        System.out.println("������������Ȩ����:" + args[0] + "\n������ĳ�Ա����Ȩ����:" + args[1] + "\n������Ļ�����:" + args[2]);
        String finall = getFinall(args);
        System.out.println("���Ա���ۺϷ���Ȩ����:" + finall);
        boolean read = getRead(args[2], finall);
        System.out.println(read ? "������Ļ����ж�����������Ա�����з���Ȩ��" : "������Ļ����ж�����������Ա����û�з���Ȩ��");
    }

    private static boolean check(String[] args) {
        if ((args == null) || (args.length != 3)) {
            System.out.println("����Ĳ���������׼ȷ,�˳�");
            return false;
        }
        HashSet<String> hs = new HashSet<>();
        hs.add("default");
        hs.add("public");
        if (!hs.contains(args[0])) {
            System.out.println("��һ�����������������Ȩ��, default��public֮һ");
            return false;
        }
        hs.add("private");
        hs.add("protected");
        if (!hs.contains(args[1])) {
            System.out.println("�ڶ���������������ĳ�Ա����Ȩ��private��default��protected��public֮һ");
            return false;
        }
        if (!args[2].equalsIgnoreCase("SameClass") && !args[2].equalsIgnoreCase("SamePackageNotSameClass") && !args[2].equalsIgnoreCase("OtherPackageSubClass") && !args[2].equalsIgnoreCase("OtherPackageNotSubClass")) {
            System.out.println("���������������Ƿ��ʻ���, ��SameClass��SamePackageNotSameClass��OtherPackageSubClass��OtherPackageNotSubClass֮һ");
            return false;
        }
        return true;
    }

    private static String getFinall(String[] args) {
        if (args[1].equals("private")) {
            return "private";
        } else if (args[0].equals("public") && args[1].equals("protected")) {
            return "protected";
        } else if (args[0].equals("default") || args[1].equals("default")) {
            return "default";
        } else {
            return "public";
        }
    }

    private static boolean getRead(String str, String finall) {
        switch (str.toLowerCase()) {    
            case "sameclass":
                return true;
            case "samepackagenotsameclass":
                return !finall.equals("private");
            case "otherpackagesubclass":
                return finall.equals("protected") || finall.equals("public");
            case "otherpackagenotsubclass":
                return finall.equals("public");
        }
        return true;
    }
}
