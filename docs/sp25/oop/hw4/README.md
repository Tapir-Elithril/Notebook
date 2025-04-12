This programme is a CLI software called *personal diary*.  
The software consists of four programs(.exe):

- `pdadd`:add an entity to the diary for the date,replace if an old diary of the same date already exists.
  read from stdin until `.` or `EOF`
- `pdlist[]`:list all the entities in the diary ordered by date or list all the entities in the period provided by stdin by `start` and `end`
- `pdshow`:prints the content of the entity specified by the date
- `pdremove`:remove one entity of the date(returns 0 on success and -1 on failure)
  
The software stores the diary in `diary.txt`, and reads it to the memory at the beginning of each program, and stores it back to the file at the end of the process.

The program is running under g++ (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0  

Run the program by executing `make` and `./<program_name>.exe`(in directory /program),or simply `make run<program_name>`,e.g.`make runpdadd`    

Run test by executing `make test`  
  
The result will display in the terminal.

Note:some entities already in diary.txt
```text
1.1
Sunny
New Year's Day
4.4
Rainy
QingMing
5.1
Sunny
International Labor Day
5.31
Cloudy
Dragon Boat Festival
10.1
Sunny
National Day
```

sample interaction:  
`./pdadd.exe`
```text
> Diary open succeed.
> Type `help` if you don't know what to do.
help
> `pdadd <date>` to add an entity,end by a line with a single `.` or `EOF`(`Ctrl-D` in Unix and `Ctrl-Z` in Windows).
> All the dates are in form <month>.<date>,e.g. 5.1.
> `bye` to exit the program.
pdadd 4.1
Sunny today!
Happy April Fools Day!
.
> Add 4.1
pdadd 4.2
.
> Error: Content cannot be empty!
pdadd 4.4
Rainy today!
Wish you peace and health during the QingMing Festival!
.
> Replace 4.4
```
`./pdlist.exe`
```text
> Diary open succeed.
> Type `help` if you don't know what to do.
help
> `pdlist` to list entities ordered by date.
> `pdlist [<start_date>,<end_date>] to list entities during the period.
> All the dates are in form <month>.<date>,e.g. 5.1.
> `bye` to exit the program.
pdlist
1.1
...
pdlist []
1.1
...
pdlist [4.1,6.1]
4.1
Sunny today!
Happy April Fools Day!
4.4
Rainy today!
Wish you peace and health during the QingMing Festival!
5.1
Sunny
International Labor Day
5.31
Cloudy
Dragon Boat Festival
```
`./pdshow.exe`
```text
> Diary open succeed.
> Type `help` if you don't know what to do.
help
> `pdshow <date>` to print the content specified by the date.
> All the dates are in form <month>.<date>,e.g. 5.1.
> `bye` to exit the program.
pdshow 10.1
Sunny
National Day
pdshow 10.2
> Contents Not Found!
pdshow 10.32
> Invalid Input! Try again!
```
`./pdremove.exe`
```text
> Diary open succeed.
> Type `help` if you don't know what to do.
help
> `pdremove <date>` to remove one entity of the date. 
> All the dates are in form <month>.<date>,e.g. 5.1.
> `bye` to exit the program.
pdremove 1.1
> remove succeed!
pdremove 1.2
> remove fail!
> Contents Not Found!
bye
> Bye~!
> Diary closed.
```
output:
```text
4.1
Sunny today!
Happy April Fools Day!
4.4
Rainy today!
Wish you peace and health during the QingMing Festival!
5.1
Sunny
International Labor Day
5.31
Cloudy
Dragon Boat Festival
10.1
Sunny
National Day
```
Additional test for `pdadd`(concerning `EOF`)
```text
> Diary open succeed.
> Type `help` if you don't know what to do.
pdadd 4.4
Rainy today!
Wish you peace and health during the QingMing Festival!
<Ctrl + D><Ctrl + D>
> Replace 4.4
> Bye~!
> Diary close succeed.
```


