# Indoor Ambient Monitoring
Arduino implementation for indoor ambient monitoring

## Compile and upload to a board

Compile

```
arduino-cli compile --fqbn esp32:esp32:esp32 --export-binaries  .
```

Upload

```
arduino-cli upload --fqbn esp32:esp32:esp32 --build-path ./build/esp32.esp32.esp32 --port [port]
```

Monitor Debug Output

```
arduino-cli monitor --port [port] --config 115200
```
