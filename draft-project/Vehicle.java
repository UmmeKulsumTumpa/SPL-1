// Interface definition
public interface Vehicle {
    
    // Constant field
    public static final int MAX_SPEED = 120;
    
    // Abstract method declarations
    void start();
    void stop();
    void accelerate(int speed, int range);
    void decelerate(int speed);
}
