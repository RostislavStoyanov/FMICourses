import java.sql.*;
import java.util.*;

public class Main
{
    private static String url;
    private static Properties props;
    private static boolean running;
    private static Scanner sc;

    private static int getMaxLength(List<ArrayList<String>> values, int index)
    {
        int max = 0, currLength;

        ArrayList<String> column = values.get(index);

        for (String str: column)
        {
            currLength = str.length();
            if (currLength > max)
            {
                max = currLength;
            }
        }

        return max;
    }

    private static String createSpacesString(int length)
    {
        StringBuilder outputBuffer = new StringBuilder(length);
        for (int i = 0; i < length; i++)
        {
            outputBuffer.append(" ");
        }
        return outputBuffer.toString();
    }

    private static void formattedPrintToConsole(List<ArrayList<String>> values, ArrayList<Integer> lengths)
    {
        int len = values.get(0).size(), diff;
        for (int i = 0; i < len; i++)
        {
            for (int j = 0; j < values.size(); j++)
            {
                String currString = values.get(j).get(i);
                diff = lengths.get(j) - currString.length();
                System.out.printf("|%s%s|", createSpacesString(diff), currString);
            }
            System.out.println();
        }
    }

    private static void printResultSet(ResultSet rs) throws SQLException
    {
        System.out.println("\n Result:");
        ResultSetMetaData rsmd = rs.getMetaData();
        int columnsCount = rsmd.getColumnCount();

        List<String> columns = new LinkedList<>();
        ArrayList<ArrayList<String>> values = new ArrayList<>();
        boolean firstRowVisited = false;

        for (int i = 0; i < columnsCount; i++)
        {
            values.add(new ArrayList<>());
        }

        while (rs.next())
        {
            for (int i = 0; i < columnsCount; i++)
            {
                if (!firstRowVisited)
                {
                    columns.add(rsmd.getColumnName(i + 1));
                }
                String columnValue = rs.getString(i + 1);
                values.get(i).add(columnValue);
            }
            firstRowVisited = true;
        }

        ArrayList<Integer> lengths = new ArrayList<>();
        int i = 0, currLength, currMaxLength, diff;
        for (String str : columns)
        {
            currLength = str.length();
            currMaxLength = getMaxLength(values, i++);
            if (currLength > currMaxLength)
            {
                lengths.add(currLength);

                System.out.printf("|%s|", str);
            }
            else
            {
                lengths.add(currMaxLength);

                diff = currMaxLength - currLength;
                System.out.printf("|%s%s|", createSpacesString(diff), str);
            }
        }

        System.out.println();

        formattedPrintToConsole(values, lengths);

    }

    private static void setUp()
    {
        sc = new Scanner(System.in);
        String host, port, database, user, pass, schema;
        running = false;

        System.out.println("--------");
        System.out.print("Enter host: ");
        host = sc.nextLine();
        System.out.print("Enter port: ");
        port = sc.nextLine();
        System.out.print("Enter database: ");
        database = sc.nextLine();
        System.out.print("Enter user: ");
        user = sc.nextLine();
        System.out.print("Enter password: ");
        pass = sc.nextLine();
        System.out.print("Enter schema: ");
        schema = sc.nextLine();


        url = "jdbc:postgresql://" + host + ":" + port + "/" + database;
        props = new Properties();
        props.setProperty("user", user);
        props.setProperty("password", pass);
        props.setProperty("currentSchema", schema);
    }

    private static void userInput(Statement st) throws SQLException
    {
        running = true;
        int input;
        String arg, query = null;
        ResultSet rs;


        while (running)
        {
            printSelectionMenu();
            input = Integer.parseInt(sc.nextLine());

            if (input == 6)
            {
                running = false;
                continue;
            }

            System.out.println("Input argument: ");
            arg = sc.nextLine();

            if(input >= 1 && input < 6)
            {
                switch(input)
                {
                    case 1:
                        query = "SELECT * FROM Book WHERE ISBN = " + arg + ";";
                        break;
                    case 2:
                        query = "SELECT * FROM Book WHERE Title LIKE \'%" + arg + "%\';";
                        break;
                    case 3:
                        query = "SELECT * FROM Book WHERE ISBN in (" +
                                "SELECT w.ISBN FROM WrittenBy w JOIN Person p ON p.PersonalNo = w.PersonalNo " +
                                "WHERE p.Name LIKE \'%" + arg + "%\');";
                        break;
                    case 4:
                        query = "SELECT * FROM Book WHERE PublisherID = (" +
                                "SELECT PublisherID FROM Publisher p " +
                                "WHERE p.Name LIKE \'%" + arg + "%\');";
                        break;
                    case 5:
                        query = "SELECT * FROM Book WHERE ISBN = (" +
                                "SELECT ISBN FROM Inventory i " +
                                "WHERE i.SystemNo LIKE \'%" + arg + "%\');";
                        break;
                }

                rs = st.executeQuery(query);
                printResultSet(rs);
            }

            else
            {
                System.out.println("Invalid input");
            }

        }

        sc.close();
    }

    private static void printSelectionMenu()
    {
        System.out.println("--------");
        System.out.println("Choose filter to run find book:");
        System.out.println(" 1)ISBN");
        System.out.println(" 2)Title");
        System.out.println(" 3)Author");
        System.out.println(" 4)Publisher");
        System.out.println(" 5)SystemNo");
        System.out.println(" 6)Exit");
    }

    public static void main(String[] args) throws SQLException
    {
        System.out.println("Library database connection application");

        setUp();
        Connection conn = DriverManager.getConnection(url, props);

        Statement st = conn.createStatement();
        userInput(st);

        /* Not very efficient using for demonstration purposes only
            (I double anyone will use it to display 100000 entries to console anyway).
         */

        st.close();
    }

}
