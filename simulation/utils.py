def to_short(value: [int, float], unit: str = "") -> str:
    prefixes = {
        -9: "r",
        -8: "y",
        -7: "z",
        -6: "a",
        -5: "f",
        -4: "p",
        -3: "n",
        -2: "u",
        -1: "m",
        0: "",
        1: "k",
        2: "M",
        3: "G",
        4: "T",
        5: "P",
        6: "E",
        7: "Z",
        8: "Y",
        9: "R",
    }
    cnt = 0
    if abs(value) < 1:
        while not 1 <= abs(value) < 1000:
            value *= 1e3
            cnt -= 1
    else:
        while not 1 <= abs(value) < 1000:
            value /= 1e3
            cnt += 1
    if abs(value) % 1 < 1e-8:
        value = int(value)
    return f"{value}{prefixes[cnt]}{unit}"


if __name__ == "__main__":
    # Testing
    assert to_short(1e9) == "1G"
    assert to_short(10e9) == "10G"
    assert to_short(1e6) == "1M"
    assert to_short(1e3) == "1k"
    assert to_short(12e3) == "12k"
    assert to_short(1500, "Hz") == "1.5kHz"
    assert to_short(0.0005, "F") == "500uF"
    assert to_short(7.5e-9, "A") == "7.5nA"
    assert to_short(2e6, "W") == "2MW"
    assert to_short(0.001, "V") == "1mV"
    assert to_short(999, "g") == "999g"
    assert to_short(-0.000123, "m") == "-123um"
    assert to_short(-0.0001, "V") == "-100uV"
    assert to_short(-99, "g") == "-99g"
