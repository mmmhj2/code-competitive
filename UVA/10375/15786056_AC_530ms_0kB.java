

import java.util.*;
import java.math.*;

public class Main {
	
	static BigInteger Fact[] = new BigInteger[10010];
	static void CalcFact()
	{
		Fact[0] = new BigInteger("" + 1);
		for(int i = 1; i < 10010; i++)
		{
			Fact[i] = new BigInteger("" + 1);
			Fact[i] = Fact[i-1].multiply(new BigInteger ("" + i));
		}
	}
	
	static public void main(String Args[])
	{
		CalcFact();
		int p, q, r, s;
		Scanner cin = new Scanner(System.in);
		while(cin.hasNextInt())
		{
			p = cin.nextInt();
			q = cin.nextInt();
			r = cin.nextInt();
			s = cin.nextInt();
			
			BigDecimal C1 = new BigDecimal(Fact[p].divide(Fact[p-q].multiply(Fact[q])));
			BigDecimal C2 = new BigDecimal(Fact[r].divide(Fact[r-s].multiply(Fact[s])));
			
			System.out.println(C1.divide(C2, 5, BigDecimal.ROUND_HALF_UP).toString());
		}
				
		cin.close();
	}
}
