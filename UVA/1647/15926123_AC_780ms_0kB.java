
import java.util.*;
import java.math.*;

public class Main {
	
	static final int MAXN = 1000 + 10;
	static BigInteger a[] = new BigInteger [MAXN];
	
	public static void main(String[] args) {
		
		Scanner cin = new Scanner(System.in);
		
		a[1] = BigInteger.valueOf(0);
		a[2] = BigInteger.valueOf(1);
		
		for(int i = 3; i < MAXN; i++)
			a[i] = a[i-1].add(a[i-2].multiply(BigInteger.valueOf(2)));
		
		while(cin.hasNextInt())
		{
			int id = cin.nextInt();
			System.out.println(a[id]);
		}
		
		cin.close();
	}

}
