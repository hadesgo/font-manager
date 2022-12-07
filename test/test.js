const { getAvailableFontsSync, findFontsSync, substituteFontSync, findFontSync } = require('bindings')('font-querier.node');
const util = require('util')

console.log(util.inspect(getAvailableFontsSync()))
console.log(findFontsSync({ family: 'Arial' }))
console.log(findFontSync({ family: '黑体', weight: 400 }))
console.log(substituteFontSync('TimesNewRomanPSMT', '汉字'))