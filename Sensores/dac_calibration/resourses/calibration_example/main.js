import { graph2D, linspace } from 'scigrapher'

const test_codes = linspace(100, 4000, 11)

const real_data = [
  0.14, // code 100
  0.61, // code 490
  1.07, // code 880
  1.52, // code 1270
  1.97, // code 1660
  2.43, // code 2050
  2.87, // code 2440
  3.29, // code 2830
  3.69, // code 3220
  4.06, // code 3610
  4.42  // code 4000
]

const calibrated_data = [
  0.14,
  0.67,
  1.17,
  1.67,
  2.17,
  2.67,
  3.15,
  3.60,
  4.02,
  4.42
]

const calibrated_codes = [
  172,
  565,
  958,
  1351,
  1744,
  2137,
  2530,
  2923,
  3316,
  3709
]

const graph = graph2D(document.querySelector("#container"))
  .containerSize({width:700, height:394})
  .axisPosition("bottom-left")
  .title({text:"MCP4725 Output Response"})
  .subtitle({text:".", opacity:0})
  .xLabel({text:"Code"})
  .yLabel({text:"Output Voltage"})
  .axisUnits({y:"v"})
  .axisDomain({x:{start:0, end:4095}, y:{start:0, end:5.05}})
  .axisTicks({x:{ticks:test_codes}})

const ideal = graph.addDataset("linechart")
  .dataX([0, 4095])
  .dataY([0, 5])
  .lineOpacity(0.8)

const real = graph.addDataset("linechart")
  .dataX(test_codes)
  .dataY(real_data)
  .lineColor("red")
  .lineOpacity(0.8)
  .markerEnable(true)
  .markerColor("red")
  .markerFilled(false)
  .markerSize(0.5)

const calibrated = graph.addDataset("linechart")
  .dataX(calibrated_codes)
  .dataY(calibrated_data)
  .lineColor("green")
  .lineOpacity(0.8)
  .markerEnable(true)
  .markerColor("green")
  .markerFilled(false)
  .markerSize(0.5)
  .markerType("square")

graph.addLegend()
  .data([
    {dataset:ideal.id(), label:"Ideal"},
    {dataset:real.id(), label:"Real"},
    {dataset:calibrated.id(), label:"Calibrated"}
  ])
  .position("top-left")

graph.draw()