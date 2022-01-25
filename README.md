# Touch Portal zTools Plugin

![Download]()

- [Touch Portal zTools Plugin](#touch-portal-ztools-plugin)
  - [Changelog](#changelog)
  - [Description](#description)
  - [Install](#install)
  - [Actions](#actions)
    - [Operators](#operators)
    - [If Then Operator](#ifthenoperators)
    - [If Then Else Operator](#ifthenelseoperators)
    - [SubString](#substring)
    - [Mid](#mid)
    - [Left](#left)
    - [Right](#right)
    - [Starts With](#startswith)
    - [Ends With](#endswith)
    - [Length](#length)
    - [Scrolling Marquee](#scrollingmarquee)
    - [Screen Capture](#screencapture)
    - [Window Capture](#windowcapture)
  - [Events](#events)
    - [Timer](#timer)
  - [Connectors](#connectors)
    - [Get Slider Value](#getslidervalue)
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
        - Operators - Get a Boolean result comparing 2 values.
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
