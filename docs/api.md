# ArduinoGraphics Library

## Methods

### `begin()`

Description
Initializes the graphics device.

#### Syntax

`YourScreen.begin()`

#### Parameters

None

#### Returns

1 for success, 0 on failure.

#### Example

```arduino
if (!YourScreen.begin() {
  Serial.println(“Failed to initialize the display!”);
  while (1);
}
```

### `end()`

Description
Stops the graphics device.

#### Syntax

`YourScreen.end()`

#### Parameters

None

#### Returns

Nothing

#### Example

```arduino
YourScreen.end();
```
