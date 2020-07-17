const path = require('path')
module.exports = path.resolve('prebuilds/' + process.platform + '-' + process.arch + (process.platform === 'win32' ? '.exe' : ''))
