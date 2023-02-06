class SourceCode{

    public static int summationOfTwoNumbers(int a, int b){
        return a+b;
    }

    public static void main(String[] args) {
        System.out.println("Hello");
        System.out.println("This is a Simple Java code");
        // single line comment
        System.out.println("This will add two integer numbers and show the result");
        /*
        multi-line comment
         */

        int a=10, b=20;

        /**
         * This is a
         * doccumentation
         * comment
         */

        int sum=summationOfTwoNumbers(a,b);

        // this is a single line comment

        System.out.printf("%d + %d = %d\n",a,b,sum);

        /*
            this is a multiple line
            comment!
        */
    }
}