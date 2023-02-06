class SourceCode{

    public static int summationOfTwoNumbers(int a, int b){
        return a+b;
    }

    public static void main(String[] args) {
        System.out.println("Hello");
        System.out.println("This is a Simple Java code");
        System.out.println("This will add two integer numbers and show the result");

        int a=10, b=20;
        int sum=summationOfTwoNumbers(a,b);

        // this is a single line comment

        System.out.printf("%d + %d = %d\n",a,b,sum);

        /*
            this is a multiple line
            comment!
        */
    }
}

// public class SourceCode {
//     private String URL;
//     private String name;
//     private String password;

//     public SourceCode(String URL, String name, String password){
//         this.URL=URL;
//         this.name=name;
//         this.password=password;
//     }

//     // getter and setter for URL
//     public String getURL() {
//         return URL;
//     }

//     public void setURL(String URL) {
//         this.URL = URL;
//     }

//     // getter and setter for name
//     public String getName() {
//         return name;
//     }

//     public void setName(String name) {
//         this.name = name;
//     }

//     // getter and setter for password
//     public String getPassword() {
//         return password;
//     }

//     public void setPassword(String password) {
//         this.password = password;
//     }
// }