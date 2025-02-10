# Host Project

## Project Structure 

- [src](src/) - source code, implementation common modules
- [src/tests](src/tests) - unit-tests 

## Test mode:

```shell
cmake -U DEBUG_MODE ..
cmake --build .
./host
```

## Console mode:
1. Build with `-D DEBUG_MODE=1`:
```shell
cmake -D DEBUG_MODE=1 ..
cmake --build .
```
1. Start `host`
   ```shell
   ./host
   ```
1. Send command in new terminal (in `./host` directory):

    ```shell
    echo -n '<command>\n' > fifo_console_rx
    ```

## VS Code Plugins

* [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
* [CMake](https://marketplace.visualstudio.com/items?itemName=twxs.cmake)
* [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
* [Cortex-Debug](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug)
