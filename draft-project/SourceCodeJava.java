//package com.test;

import java.util.Scanner;
import java.util.ArrayList;
import java.util.LinkedList;

public class SourceCodeJava{
    
    public static int summationOfTwoNumbers(int a, int b){
        if(a>=b && b!=0){
            System.out.println("testing");
        }
        return a+b; // adds
    }

    public static boolean isGreater(int a, int b){
        if(a!=b && b!=11 || a!=12){System.out.println("");}
        return (a>=b) ? true : false;
    }

    private static void check()
    {
        if(11<12 && 13>12){

        }

        if(14-2>0){
            System.out.println();
        }
        
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

        if(flag==true){
            System.out.printf("%d is greater than %d\n", a, b);
        }
        else{
            System.out.printf("%d is smaller than %d\n", a, b);
        }

        if(a!=10 || b==56 && a!=b){

        }
        else if(b==2){
            
        }
        else if(a>0){
            System.out.println();
        }
    }

    public static void msg(){
        System.out.println("So tired!");

        if(12>0){
            System.out.println();
        }
        
        // still can't handle single and double together -_-, maybe now it can handle
        if(-12<=0 || -8<0){
            System.out.println();
        }
    }

    private void testMethod(int a, int b){
        if(a>b && a!=b){

        }
        else if(a==b || b<14){

        }

        if(a<=b){

        }
        else if(b>a){
            
        }
    }
}
