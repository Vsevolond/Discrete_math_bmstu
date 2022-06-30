package main

import (
	"fmt"
)

type fract struct {
	num int
	den int
}

func abs(val int) int {
	if val < 0 {
		return -val
	}
	return val
}

func gcd(a, b int) int {
	for b != 0 {
		a %= b
		if a == 0 {
			return abs(b)
		}
		b %= a
	}
	return abs(a)
}

func checkFract(x *fract) {
	if x.den < 0 {
		x.den = -x.den
		x.num = -x.num
	}
	if x.num == 0 {
		x.den = 1
	}
}

func minus(a, b fract) fract {
	checkFract(&a)
	checkFract(&b)
	a.num *= b.den
	b.num *= a.den
	val_num := a.num - b.num
	val_den := a.den * b.den
	val_div := gcd(val_num, val_den)
	if val_div == 0 {
		return fract{0, 1}
	}
	res := fract{val_num / val_div, val_den / val_div}
	checkFract(&res)
	return res
}

func mult(a, b fract) fract {
	checkFract(&a)
	checkFract(&b)
	val_num := a.num * b.num
	val_den := a.den * b.den
	val_div := gcd(val_num, val_den)
	if val_div == 0 {
		return fract{0, 1}
	}
	res := fract{val_num / val_div, val_den / val_div}
	checkFract(&res)
	return res
}

func div(a, b fract) fract {
	checkFract(&a)
	checkFract(&b)
	val_num := a.num * b.den
	val_den := a.den * b.num
	val_div := gcd(val_num, val_den)
	if val_div == 0 {
		return fract{0, 1}
	}
	res := fract{val_num / val_div, val_den / val_div}
	checkFract(&res)
	return res
}

func print(m [][]fract, n int) {
	for i := 0; i < n; i++ {
		for j := 0; j < n+1; j++ {
			fmt.Printf("%d/%d ", m[i][j].num, m[i][j].den)
		}
		fmt.Println()
	}
}

func main() {
	var n int
	fmt.Scan(&n)
	var m [][]fract = make([][]fract, n)
	for i := 0; i < n; i++ {
		m[i] = make([]fract, n+1)
		for j := 0; j < n+1; j++ {
			var tmp int
			fmt.Scanf("%d", &tmp)
			m[i][j] = fract{tmp, 1}
		}
	}
	for i := 0; i < n-1; i++ {
		if m[i][i].num == 0 {
			for j := i + 1; j < n; j++ {
				if m[j][i].num != 0 {
					m[i], m[j] = m[j], m[i]
					break
				}
			}
		}
	}
	start := 0
	for i := 0; i < n-1; i++ {
		for j := i + 1; j < n; j++ {
			if m[i][start].num == 0 {
				i--
				break
			} else {
				fact := div(m[j][start], m[i][start])
				for k := start; k < n+1; k++ {
					m[j][k] = minus(m[j][k], mult(m[i][k], fact))
				}
			}
		}
		start++
	}
	var res []fract = make([]fract, n)
	var comp bool = true
	for i := 0; i < n && comp; i++ {
		comp = false
		for j := 0; j < n; j++ {
			comp = comp || (m[i][j].num != 0)
		}
		if !comp {
			fmt.Println("No solution")
			return
		} else {
			comp = true
		}
	}
	for l := n - 1; l >= 0; l-- {
		for r := l + 1; r < n; r++ {
			m[l][n] = minus(m[l][n], mult(m[l][r], res[r]))
		}
		res[l] = div(m[l][n], m[l][l])
	}
	for _, elem := range res {
		fmt.Printf("%d/%d\n", elem.num, elem.den)
	}

}
