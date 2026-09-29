# Arduino Redox Potential Meter

A documented portfolio version of the Redox Potential Meter developed as a Medical Engineering semester project at the Asian Institute of Technology from January to May 2025.

## Project scope

- Arduino based acquisition and serial reporting
- Ag/AgCl reference electrode fabrication
- Platinum sensing electrode preparation
- Calibration and comparative measurements
- Solution preparation using NaCl and ammonium hexachloroplatinate

## Essential hardware note

Do not connect an electrochemical electrode pair directly to a standard Arduino analogue input. ORP and redox electrodes require a very high input impedance signal conditioning stage, appropriate electrical isolation and careful calibration. The included sketch assumes that a suitable front end produces a safe analogue voltage within the Arduino ADC range.

## Sketch configuration

Update these constants after calibration:

```cpp
const float ZERO_ORP_OUTPUT_V = 2.500;
const float ORP_MV_PER_OUTPUT_V = 1000.0;
const float CALIBRATION_OFFSET_MV = 0.0;
```

- `ZERO_ORP_OUTPUT_V` is the front end output corresponding to 0 mV ORP.
- `ORP_MV_PER_OUTPUT_V` is the conversion slope from front end voltage to electrode millivolts.
- `CALIBRATION_OFFSET_MV` stores the verified correction from a reference solution.

## Serial output

The sketch reports:

```text
time_ms,adc_mean,signal_voltage_v,orp_mv
```

This makes the measurements easy to save and analyse in Excel, MATLAB or Python.

## Scientific and safety limitations

- This is educational portfolio code, not a certified medical or industrial instrument.
- Calibration values in the sketch are placeholders and must be replaced with experimental values.
- Use suitable personal protective equipment and institutional procedures when preparing electrode materials and chemical solutions.
- Never use the instrument for clinical decisions or patient care.

## Author

**Shoaib Akhtar**  
Medical Engineering researcher, Asian Institute of Technology  
[GitHub profile](https://github.com/shoaib7433-draib) · [LinkedIn](https://www.linkedin.com/in/shoaib-akhtar-919a373aa/)

## Licence

MIT License. See `LICENSE`.
