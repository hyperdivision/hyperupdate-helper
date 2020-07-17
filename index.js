const path = require('path')
module.exports = path.join(__dirname, 'prebuilds/' + process.platform + '-' + process.arch + (process.platform === 'win32' ? '.exe' : ''))
