package main

/*var a = []int{
	16, 25, 27, 31, 33, 42, 42, 49, 59, 69,
	74, 81, 90, 100,
}

var expected = []int{
	16, 25, 27, 31, 33, 42, 42, 49, 59, 69,
	74, 81, 90, 100,
}

func less(i, j int) bool {
	return a[i] < a[j]
}

func swap(i, j int) {
	a[i], a[j] = a[j], a[i]
}*/

func partition(l, r int, less func(i, j int) bool, swap func(i, j int)) int {
	i := l
	j := l
	for j < r {
		if less(j, r) {
			swap(i, j)
			i++
		}
		j++
	}
	swap(i, r)
	return i
}

func quicksort(l, r int, less func(i, j int) bool, swap func(i, j int)) {
	if l < r {
		q := partition(l, r, less, swap)
		quicksort(q+1, r, less, swap)
		quicksort(l, q-1, less, swap)
	}
}

func qsort(n int, less func(i, j int) bool, swap func(i, j int)) {
	quicksort(0, n-1, less, swap)
}

func main() {

}
