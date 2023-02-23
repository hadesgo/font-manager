const { getAvailableFontsSync, findFontsSync, substituteFontSync, findFontSync } = require('bindings')('font-querier.node');
const util = require('util')

// console.log(util.inspect(getAvailableFontsSync()))
// console.log(findFontsSync({ family: 'Arial' }))

const test = () => {
    try {
        const start = performance.now();
        const fontInfo = findFontSync({ family: '隶书', weight: 400 })
        console.log(fontInfo)
        const end = performance.now();
        console.log('cost is', `${end - start}ms`)
    } catch (error) {
        console.log(error)
    }
}
test()