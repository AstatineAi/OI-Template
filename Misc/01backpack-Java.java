import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int v = sc.nextInt();
        int n = sc.nextInt();
        int[] dp = new int[1005];
        int[] w = new int[105];
        int[] c = new int[105];
        for(int i = 1;i <= n;++i) {
        	w[i] = sc.nextInt();
        	c[i] = sc.nextInt();
        }
        for(int i = 1;i <= n;++i) {
        	for(int j = v;j >= w[i];--j) {
        		dp[j] = Math.max(dp[j],dp[j - w[i]] + c[i]);
        	}
        }
        System.out.println(dp[v]);
    }
}