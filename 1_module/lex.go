package main

import (
	"fmt"
)

//var text = "alpha x1 beta alpha x1 y"

type AVL struct {
	key    string
	value  int
	height int
	left   *AVL
	right  *AVL
}

func (t *AVL) Search(key string) (int, bool) {
	if t == nil {
		return 0, false
	}
	if key < t.key {
		return t.left.Search(key)
	} else if key > t.key {
		return t.right.Search(key)
	} else {
		return t.value, true
	}
}

func (t *AVL) leftRotate() *AVL {
	headNode := t.right
	t.right = headNode.left
	headNode.left = t
	t.height = max(t.left.getHeight(), t.right.getHeight()) + 1
	headNode.height = max(headNode.left.getHeight(), headNode.right.getHeight()) + 1
	return headNode
}

func (t *AVL) rightRotate() *AVL {
	headNode := t.left
	t.left = headNode.right
	headNode.right = t
	t.height = max(t.left.getHeight(), t.right.getHeight()) + 1
	headNode.height = max(headNode.left.getHeight(), headNode.right.getHeight()) + 1
	return headNode
}

func (t *AVL) rightThenLeftRotate() *AVL {
	sonHeadNode := t.right.rightRotate()
	t.right = sonHeadNode
	return t.leftRotate()
}

func (t *AVL) LeftThenRightRotate() *AVL {
	sonHeadNode := t.left.leftRotate()
	t.left = sonHeadNode
	return t.rightRotate()
}

func (t *AVL) adjust() *AVL {
	if t.right.getHeight()-t.left.getHeight() == 2 {
		if t.right.right.getHeight() > t.right.left.getHeight() {
			t = t.leftRotate()
		} else {
			t = t.rightThenLeftRotate()
		}
	} else if t.left.getHeight()-t.right.getHeight() == 2 {
		if t.left.left.getHeight() > t.left.right.getHeight() {
			t = t.rightRotate()
		} else {
			t = t.LeftThenRightRotate()
		}
	}
	return t
}

func (t *AVL) Insert(key string, value int) *AVL {
	if t == nil {
		newNode := AVL{key, value, 1, nil, nil}
		return &newNode
	}
	if key < t.key {
		t.left = t.left.Insert(key, value)
		t = t.adjust()
	} else if key > t.key {
		t.right = t.right.Insert(key, value)
		t = t.adjust()
	} else {
		t.value = value
	}
	t.height = max(t.left.getHeight(), t.right.getHeight()) + 1
	return t
}

func (t *AVL) Delete(key string) *AVL {
	if t == nil {
		return t
	}
	if key < t.key {
		t.left = t.left.Delete(key)
	} else if key > t.key {
		t.right = t.right.Delete(key)
	} else {
		if t.left != nil && t.right != nil {
			t.value = t.right.getMin()
			t.right = t.right.Delete(t.key)
		} else if t.left != nil {
			t = t.left
		} else {
			t = t.right
		}
	}
	if t != nil {
		t.height = max(t.left.getHeight(), t.right.getHeight()) + 1
		t = t.adjust()
	}
	return t
}

func (t *AVL) getAll() []string {
	values := []string{}
	return addValues(values, t)
}

func addValues(values []string, t *AVL) []string {
	if t != nil {
		values = addValues(values, t.left)
		values = append(values, t.key)
		fmt.Println(t.value, t.height)
		values = addValues(values, t.right)
	}
	return values
}

func (t *AVL) getMin() int {
	if t == nil {
		return -1
	}
	if t.left == nil {
		return t.value
	} else {
		return t.left.getMin()
	}
}

func (t *AVL) getMax() int {
	if t == nil {
		return -1
	}
	if t.right == nil {
		return t.value
	} else {
		return t.right.getMax()
	}
}

func (t *AVL) getMinNode() *AVL {
	if t == nil {
		return nil
	} else {
		for t.left != nil {
			t = t.left
		}
	}
	return t
}

func (t *AVL) getMaxNode() *AVL {
	if t == nil {
		return nil
	} else {
		for t.right != nil {
			t = t.right
		}
	}
	return t
}

func (t *AVL) getHeight() int {
	if t == nil {
		return 0
	}
	return t.height
}

func max(a int, b int) int {
	if a > b {
		return a
	} else {
		return b
	}
}

type AssocArray interface {
	Assign(s string, x int)
	Lookup(s string) (x int, exists bool)
}

/*type UnitTestAssocArray map[string]int

func (m UnitTestAssocArray) Assign(s string, x int) {
	m[s] = x
}

func (m UnitTestAssocArray) Lookup(s string) (x int, exists bool) {
	x, exists = m[s]
	return
}*/

type Tree struct {
	root *AVL
}

func (t *Tree) Assign(s string, x int) {
	t.root = t.root.Insert(s, x)
}

func (t *Tree) Lookup(s string) (x int, exists bool) {
	return t.root.Search(s)
}

func (t *Tree) get() []string {
	return t.root.getAll()
}

func lex(sentence string, array AssocArray) []int {
	words := make([]string, 0)
	var word string
	for _, x := range sentence {
		if x != ' ' {
			word += string(x)
		} else {
			if len(word) > 0 {
				words = append(words, word)
				word = ""
			}
		}
	}
	if len(word) > 0 {
		words = append(words, word)
	}
	cnt := 1
	res := make([]int, 0)
	for _, word = range words {
		val, exist := array.Lookup(word)
		if exist {
			res = append(res, val)
		} else {
			array.Assign(word, cnt)
			res = append(res, cnt)
			cnt++
		}
	}
	return res
}

func main() {
	/*var m = make(UnitTestAssocArray)
	actual := lex(text, m)
	fmt.Println(actual)*/
}
