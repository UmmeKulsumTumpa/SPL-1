package com.test;

import java.util.Scanner;
import java.util.ArrayList;
import java.util.LinkedList;

public class SourceCodeJava{
    
    public static int summationOfTwoNumbers(int a, int b){
        return a+b; // adds
    }

    public static boolean isGreater(int a, int b){
        return (a>b) ? true : false;
    }

    private static int check(){
        return 2;
    }

    public static void main(String[] args){
        System.out.println("Hello");
        System.out.println("This is a Simple Java code");
        // single line comment
        System.out.println("This will add two integer numbers and show the result");
        /*
        multi-line comment
         */

        int a=10, b=20; // another comment

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

        boolean flag=isGreater(a, b);

        if(flag){
            System.out.printf("%d is greater than %d\n", a, b);
        }
        else{
            System.out.printf("%d is smaller than %d\n", a, b);
        }
    }

    public static void msg(){
        System.out.println("So tired!");
    }
}
