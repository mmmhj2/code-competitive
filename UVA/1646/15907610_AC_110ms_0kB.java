
import java.util.*;
import java.math.*;

public class Main {
	static BigInteger fib[] = new BigInteger[10000 + 10];
	
	public static void main(String[] args) {
		
		Scanner cin = new Scanner(System.in);
		
		fib[3] = BigInteger.valueOf(4);
		fib[4] = BigInteger.valueOf(7);
		
		for(int i = 5; i <= 10000; i++)
			fib[i] = fib[i-1].add(fib[i-2]);
		
		while(cin.hasNextInt())
		{
			int N = cin.nextInt();
			System.out.println(fib[N]);
		}
		
		cin.close();
	}

}
