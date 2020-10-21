void main() {
        Console.WriteLine("Welcome to CadexCalculator!");
        Console.WriteLine("The official Calculator for CadexOS.");
        Console.WriteLine("Enter the numbers you want to multiply below.");
        Console.Write("Enter the first number");
        double num1 = Convert.ToDouble(Console.ReadLine());

        Console.Write("Enter your opearator(x,÷,-,+)");
        string op = Console.ReadLine();

        Console.Write("Enter the second number");
        double num2 = Convert.ToDouble(Console.ReadLine());

        if (op == "+") {
            Console.WriteLine(num1 + num2);
        } else if (op == "-") {
            Console.WriteLine(num1 - num2);
        } else if (op == "*") {
            Console.WriteLine(num1 * num2);
        } else if (op == "/") {
            Console.WriteLine(num1 / num2);
        } else {
            Console.WriteLine("Invalid Operator");
        }
        Console.ReadLine();
    }
}
}
