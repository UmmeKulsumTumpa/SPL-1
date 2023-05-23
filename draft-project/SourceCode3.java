import java.util.ArrayList;
import java.util.Scanner;
import java.util.Vector;

public class SourceCode3{

    static int n=1;
    static int m=2;
    ArrayList<Integer> intList=new ArrayList<>();
    ArrayList<Integer> list2;

    static void funcMethod(){
        if(n==m){
            return;
        }
        if(n<m){
            funcMethod();
        }
        return;
    }

    private int num1;
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        int b=0,c=1;
        funcMethod();
        try{
            int a=sc.nextInt();
        }
        catch(Exception e){

        }
        finally{
            if(true){
                System.out.println();
            }
            if(b>c){
                System.out.println();
            }
            else
            {
                System.out.println(b);
            }
        }
        return;
    }

    int num2, num3=0, 
    num4;

    String name;

    int[] intArray={1, 8, 3, 4},
            Array2={2,6,8};
    ArrayList<String> stringList={"blue", "black"}; float val1, val2=9.87;

    void fun1(){

    }

    Double balance=0.0, net_worth;
}
