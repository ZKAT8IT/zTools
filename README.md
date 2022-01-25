# Touch Portal zTools Plugin

![Download](https://github.com/ZKAT8IT/zTools/blob/main/download/zTools-v0.8.tpp)

- [Touch Portal zTools Plugin](#touch-portal-ztools-plugin)
  - [Changelog](#changelog)
  - [Description](#description)
  - [Install](#install)
  - [Actions](#actions)
    - [Operators](#operators)
    - [If Then Operator](#if-then-operator)
    - [If Then Else Operator](#if-then-else-operator)
    - [SubString](#substring)
    - [Mid](#mid)
    - [Left](#left)
    - [Right](#right)
    - [Starts With](#starts-with)
    - [Ends With](#ends-with)
    - [Length](#length)
    - [Scrolling Marquee](#scrolling-marquee)
    - [Screen Capture](#screen-capture)
    - [Window Capture](#window-capture)
  - [Events](#events)
    - [Timer](#timer)
  - [Connectors](#connectors)
    - [Get Slider Value](#get-slider-value)
  - [States](#states)
    - [Operator States](#operator-states)
    - [String States](#string-states)
    - [Marquee States](#marquee-states)
    - [Screen States](#screen-states)
    - [Connector States](#connector-states)
  - [Issues](#issues)
  - [Author](#author)

## Changelog
```
0.8 - The initial release
    - Actions
        - Operators - Get a Boolean result comparing 2 values. ( Operators are == , != , >= , <= , > , < , * , / , + , - )
        - If Then Operator - Compare 2 Values/States and store a value upon sucess.
        - If Then Else Operator - Compare 2 Values/States and store a value upon success/fail.
        - SubString - Obtain a portion of the string defining the Start and End point.
        - Mid - Obtain a portion of the string defining the Start poing and number of characters.
        - Left - Returns the first count characters of the string.
        - Right - Returns the last count characters of the string.
        - Starts With - Returns Boolean result if first value starts with second value.
        - Ends With - Returns Boolean result if first value ends with second value.
        - Length - Returns the length of the value.
        - Scrolling Marquee - Returns a portion of the string provided with length set.
        - Screen Capture - Will return a 128x128 Image capture of the screen at designated coordinates.
        - Window Capture - Will return a 128x128 Image capture of the application at designated coordinates.
    - Events
        - Timer - Repeat Actions at set intervals.
    - Connectors
        - Get Slider Value - Obtain the value of a slider and store it.
    - States
        - opResults - States used to store Operation results.
        - strResults - States used to store String results.
        - sMarquee - Stated used to store Marquee results.
        - sCapture - States used to store Screen/Window Capture images.
        - conResult - States used to store Slider values.

```

## Description
These are basic programming functions plus some extra tools added to make customizing touch portal easier. 

- Warning: It is advised when using any of the returned results ( States ) from any Actions from this plugin, in succession, to use a "Wait for Timer" Action to allow the plugin to process the result and return it. Touch Portal and this plugin run separately and failing to allow time for the value to be returned may produce undesired results.

This is still being worked on and there may be bugs or unpredictable results.

## Install

1. Import the .tpp file into Touch Portal
2. Click Okay and Trust Always

## Actions

### Operators

Get a Boolean result comparing 2 values. ( 0 for False, 1 for True )
 - Note: If using Text instead of Numbers it will use the length of the Text.

![Operators](resources/Operators.png)

### If-Then Operator

Compare 2 Values/States and store a value upon sucess.
 - Note: If using Text instead of Numbers it will use the length of the Text.

![If Then Operator](resources/IfThenOperator.png)

### If-Then-Else Operator

Compare 2 Values/States and store a value upon success/fail.
- Note: If using Text instead of Numbers it will use the length of the Text.

![If Then Else Operator](resources/IfThenElseOperator.png)

### SubString

Obtain a portion of the string defining the Start and End point.

![SubString](resources/SubString.png)

### Mid

Obtain a portion of the string defining the Start poing and number of characters.

![Mid](resources/Mid.png)

### Left

Returns the first count characters of the string.

![Left](resources/Mid.png)

### Right

Returns the last count characters of the string.

![Right](resources/Right.png)

### Starts With

Returns Boolean result if first value starts with second value. ( 0 for False, 1 for True )

![Starts With](resources/StartsWith.png)

### Ends With

Returns Boolean result if first value ends with second value. ( 0 for False, 1 for True )

![Ends With](resources/EndsWith.png)

### Length

Returns the length of the value.

![Length](resources/Length.png)

### Scrolling Marquee

Returns a portion of the string provided with length set.

![Scrolling Marquee](resources/ScrollingMarquee.png)

### Screen Capture

Will return a 128x128 Image capture of the screen at designated coordinates.

![Screen Capture](resources/ScreenCapture.png)

### Window Capture

Will return a 128x128 Image capture of the application at designated coordinates.

![Window Capture](resources/WindowCapture.png)

## Events

### Timer

Repeat Actions at set intervals.

![Timer](resources/Timer.png)

## Connectors

### Get Slider Value

Obtain the value of a slider and store it.

![Get Slider Value](resources/SliderValue.png)

## States

This plugin gives you 10 states of each.
  - opResults - States used to store Operation results.
  - strResults - States used to store String results.
  - sMarquee - Stated used to store Marquee results.
  - sCapture - States used to store Screen/Window Capture images.
  - conResult - States used to store Slider values.

## Issues
Please report issues on the #zTools channel on the Official Touch Portal Discord.

## Author
James Burns (aka ZKAT8IT)
