import java.util.ArrayList;
import java.util.Stack;

public class SourceCode4 {
    private int number;
    private String text;
    private boolean flag;
    private double value;
    private ArrayList<String> stringList;
    private Stack<Integer> numberStack;

    public SourceCode4(int number, String text, boolean flag, double value) {
        this.number = number;
        this.text = text;
        this.flag = flag;
        this.value = value;
        this.stringList = new ArrayList<>();
        this.numberStack = new Stack<>();
        initializeList();
        initializeStack();
    }

    public void initializeList() {
        stringList.add("One");
        stringList.add("Two");
        stringList.add("Three");
    }

    public void initializeStack() {
        numberStack.push(1);
        numberStack.push(2);
        numberStack.push(3);
    }

    public void displayNumber() {
        System.out.println("Number: " + number);
    }

    public void displayText() {
        System.out.println("Text: " + text);
    }

    public void processInput(String input) {
        try {
            int parsedNumber = Integer.parseInt(input);
            if (parsedNumber > number) {
                System.out.println("Input number is greater than the stored number.");
            } else {
                System.out.println("Input number is smaller than or equal to the stored number.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid number.");
        }
    }

    public void printNumbersInRange(int start, int end) {
        for (int i = start; i <= end; i++) {
            System.out.print(i + " ");
        }
        System.out.println();
    }

    public void displayFlag() {
        System.out.println("Flag: " + flag);
    }

    public void displayValue() {
        System.out.println("Value: " + value);
    }

    public void displayList() {
        System.out.println("String List: " + stringList);
    }

    public void displayStack() {
        System.out.println("Number Stack: " + numberStack);
    }

    public static void main(String[] args) {
        SourceCode4 example = new SourceCode4(10, "Hello", true, 3.14);

        example.displayNumber();
        example.displayText();

        example.processInput("15");
        example.processInput("5");
        example.processInput("abc");

        example.printNumbersInRange(1, 5);

        example.displayFlag();
        example.displayValue();

        example.displayList();
        example.displayStack();
    }
}
