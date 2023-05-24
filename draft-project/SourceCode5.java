import java.util.ArrayList;
import java.util.List;

public abstract class SourceCode5 {
    // Fields
    private String name;
    private int age;
    private List<String> hobbies;

    // Constructor
    public SourceCode5(String name, int age) {
        this.name = name;
        this.age = age;
        this.hobbies = new ArrayList<>();
    }

    // Abstract method
    public abstract void abstractMethod();

    // Non-abstract method
    public void nonAbstractMethod() {
        System.out.println("This is a non-abstract method.");
    }

    // Method with logical statements and loops
    public void processHobbies() {
        if (hobbies.isEmpty()) {
            System.out.println("No hobbies found.");
        } else {
            System.out.println("Hobbies:");
            for (String hobby : hobbies) {
                System.out.println(hobby);
            }
        }
    }

    // Method with exception handling
    public void divide(int a, int b) {
        try {
            int result = a / b;
            System.out.println("Result: " + result);
        } catch (ArithmeticException e) {
            System.out.println("Error: Division by zero is not allowed.");
        }
    }

    // Getters and setters for the fields
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public List<String> getHobbies() {
        return hobbies;
    }

    public void setHobbies(List<String> hobbies) {
        this.hobbies = hobbies;
    }
}
