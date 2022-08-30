
import java.util.*;
import java.math.*;

public class Main {
	// C(n, 4) + C(n, 2) + 1 = (n^4 - 6n^3 + 23n^2 - 18n + 24) / 24
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		int k = cin.nextInt();

		while (k-- > 0) {
			BigInteger N, answer;
			answer = BigInteger.ZERO;
			N = cin.nextBigInteger();
			// 论支持运算符重载的好处
			answer = N.pow(4).subtract(N.pow(3).multiply(BigInteger.valueOf(6)))
					.add(N.pow(2).multiply(BigInteger.valueOf(23))).subtract(N.multiply(BigInteger.valueOf(18)))
					.add(BigInteger.valueOf(24));
			answer = answer.divide(BigInteger.valueOf(24));
			System.out.println(answer.toString());
		}

		cin.close();
	}

}
