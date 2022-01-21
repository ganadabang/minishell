# echo

```shell
> echo [-neE] [arg ...]
```

### Output the args, separated by spaces, terminated with a newline

>The return status is 0 

> -n : the trailing newline is suppressed



#### < Case >

- [x] `args` 출력
- [x] 빈칸 여러개 -> 빈칸 하나로 출력
- [x] option `-n` 일 시 `\n` 개행 제거

- [x] `option flags`가 `0`이면 `\n` 개행 출력

- [x] `single quote(' ')` 일 때 환경 변수를 치환하지 않고 그래도 출력

  ```shell
  > echo '$PATH'
  > $PATH
  
  > echo "$PATH"
  > PATH 경로 출력
  ```


- [x] option `-n == -nnnnn` 동일 하게 출력





# cd

```shell
> cd [-L] [-P [-e]] [-@] [directory]
```

### Change the current working directory to directory

> If directory is not supplied the value of the HOME shell variable is used

> Any additional arguments following directory are ignored



#### < Case >

- [x] `cd` or `cd 경로 ` 일 경우 HOME 경로를 찾아서 이동

- [x] `cd $PATH` 일 경우 `PATH` 경로 찾아서 이동 

- [x] `cd 경로` 이후에 인자가 들어올 경우 Error message 없이 경로로 이동

- [x] `cd [env에 없는 환경변수]`일 경우 HOME 경로를 찾아서 이동

- [x] `cd 222 333` 와 같이 인자 2개이상 일 때 Error 출력

  ```shell
  bash: cd: [첫번째 인자]: No such file or directory
  ```

- [ ] 올바르지 않은 폴더 경로를 인자로 받을 때 Error 출력

  ```shell
  bash: cd: [인자]: No such file or directory
  ```

- [ ] `unset HOME` 한 후 `cd $HOME` 했을 때 Error 출력

  ```shell
  bash: cd: HOME not set
  ```

- [x] `cd -` 이전 경로로 이동





# pwd

```shell
> pwd [-LP]
```

### Print the absolute pathname of the current working directory



#### < Case >

- [x] 현재 `directory 경로` 출력





# export

```shell
> export [-fn] [-p] [name[=value]]
```

### Mark each name to be passed to child processes in the environment



#### < Case >

- [x] `export` , `export $환경변수`면 `print_export`
- [x] `export` 뒤에 인자가 1개이면 환경변수에 저장 X
- [x] `export key=value`이면 환경변수에 저장 (key에 숫자 있으면 안된다.)



# unset

```shell
> unset [-fnv] [name]
```

### Remove each variable or function name



#### < Case >

- [x] `unset 환경변수` 해당 환경 변수가 있으면 삭제 O
- [x] `unset 환경변수` 해당 환경 변수가 없으면 삭제 X



# env

```shell
> env [환경변수]
```

### Print a list of environment variables 

### run another utility in an altered envirenment without having to modify the currently existing environment



#### < Case >

- [x] `env`  입력시 환경 변수 전체 출력

- [x] `env $PATH` 입력 시 PATH값에 상관 없이 환경 변수 전체 출력 

- [x] `env path` 입력 시 Error 출력

  ```shell
  env: path: No such file or directory
  ```

   



# exit

```shell
> exit [n]
```

### Exit the shell, returning a status of n to the shell's parent



#### < Case >

- [x] `exit` 입력 시 `exit` 출력 후 `shell` 끄기

- [x] `exit` 뒤의 숫자 인자 + 인자가 2개(인자 개수) 이상이면 `Error` 발생 후 `shell` 종료 X

  ```shell
  > exit 111 222 333
  exit
  bash: exit: too many arguments
  
  //but
  > exit 111
  exit 된다.
  ```

- [x] `exit` 뒤의 인자가 숫자가 아닌 경우 `Error` 발생 후 `shell` 종료 O

  ```shell
  > exit gpaeng
  exit
  bash: exit: gpaeng: numeric argument required
  ```



# Reference

https://www.gnu.org/software/bash/manual/bash.pdf
https://wiki.kldp.org/HOWTO/html/Adv-Bash-Scr-HOWTO/internal.html
