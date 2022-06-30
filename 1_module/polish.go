package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func calc(expr string, idx int) (int, int) {
	var res int
	for expr[idx] != ')' && expr[idx] != '\n' {
		if expr[idx] == '(' {
			idx++
			res, idx = operate(expr, idx, expr[idx])
		} else if expr[idx] >= '0' && expr[idx] <= '9' {
			res, _ = strconv.Atoi(string(expr[idx]))
			idx++
		} else {
			idx++
		}
	}
	return res, idx
}

func operate(expr string, idx int, op uint8) (int, int) {
	var a, b int
	var a_isCalc bool = false
	var b_isCalc bool = false
	for expr[idx] != '\n' {
		if expr[idx] == '(' {
			if a_isCalc {
				b, idx = calc(expr, idx)
				b_isCalc = true
			} else {
				a, idx = calc(expr, idx)
				a_isCalc = true
			}
		} else if expr[idx] >= '0' && expr[idx] <= '9' {
			if a_isCalc {
				b, _ = strconv.Atoi(string(expr[idx]))
				b_isCalc = true
			} else {
				a, _ = strconv.Atoi(string(expr[idx]))
				a_isCalc = true
			}
		} else if expr[idx] == ')' && a_isCalc && b_isCalc {
			break
		}
		idx++
	}
	if op == '-' {
		return a - b, idx
	} else if op == '+' {
		return a + b, idx
	} else {
		return a * b, idx
	}
}

func main() {
	var expr string
	expr, _ = bufio.NewReader(os.Stdin).ReadString('\n')
	res, _ := calc(expr, 0)
	fmt.Println(res)
}
