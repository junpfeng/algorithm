target1 = sort
obj1 = sort.o

target2 = find
obj2 = find.o

target3 = tree
obj3 = tree.o

target4 = graph
obj4 = graph.o

$(target1) : $(obj1)
	g++ $^ -o $@ -g

$(target2) : $(obj2)
	g++ $^ -o $@ 

$(target3) : $(obj3)
	g++ $^ -o $@

$(target4) : $(obj4)
	g++ $^ -o $@

clean :
	rm -f *.o $(target)


