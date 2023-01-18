class SourceCode{

    public static int summationOfTwoNumbers(int a, int b){
        return a+b;
    }
    public static void main(String[] args) {
        System.out.println("Hello");
        System.out.println("This is a Simple Java code");

        int a=10, b=20;
        int sum=summationOfTwoNumbers(a,b);

        System.out.printf("%d + %d = %d",a,b,sum);
    }
}