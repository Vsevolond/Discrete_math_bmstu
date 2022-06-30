package main

import (
	"bufio"
	"fmt"
	"os"
)

var terms = make(map[string]int)

func calc(expr string, idx int) int {
	for idx < len(expr) && expr[idx] != ')' {
		if expr[idx] == '(' {
			start_idx := idx
			idx++
			idx = operate(expr, idx)
			key := expr[start_idx : idx+1]
			_, ok := terms[key]
			if ok {
				terms[key]++
			} else {
				terms[key] = 1
			}
		} else {
			idx++
		}
	}
	return idx
}

func operate(expr string, idx int) int {
	var a_isCalc bool = false
	var b_isCalc bool = false
	for idx < len(expr) && (expr[idx] != ')' || !a_isCalc || !b_isCalc) {
		if expr[idx] == '(' {
			idx = calc(expr, idx)
			if a_isCalc {
				b_isCalc = true
			} else {
				a_isCalc = true
			}
		} else if expr[idx] >= 'a' && expr[idx] <= 'z' {
			if a_isCalc {
				b_isCalc = true
			} else {
				a_isCalc = true
			}
		}
		idx++
	}
	return idx
}

func main() {
	var expr string
	expr, _ = bufio.NewReader(os.Stdin).ReadString('\n')
	_ = calc(expr, 0)
	//for term, cnt := range terms {
	//	fmt.Printf("%s : %d\n", term, cnt)
	//}
	fmt.Println(len(terms))
}
