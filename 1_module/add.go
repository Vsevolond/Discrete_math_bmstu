package main

import "fmt"

func add(a, b []int32, p int) []int32 {
	var del int32 = int32(p)
	if len(a) < len(b) {
		a, b = b, a
	}
	var res []int32
	var q int32 = 0
	for i := 0; i < len(b); i++ {
		res = append(res, (a[i]+b[i]+q)%del)
		q = (a[i] + b[i] + q) / del
	}
	for i := len(b); i < len(a); i++ {
		res = append(res, (a[i]+q)%del)
		q = (a[i] + q) / del
	}
	if q > 0 {
		res = append(res, q)
	}
	return res
}

func myPrint(x []int32) {
	for i := len(x) - 1; i >= 0; i-- {
		fmt.Print(x[i])
	}
	fmt.Println()
}

func main() {
	var a []int32 = []int32{9}
	var b []int32 = []int32{1, 9, 9}
	myPrint(a)
	myPrint(b)
	myPrint(add(a, b, 10))
}
