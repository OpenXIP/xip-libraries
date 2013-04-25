<?xml version="1.0" encoding="ISO-8859-1"?>

<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
  <html>
  <body>
    <h2>Test Output</h2>
    <table border="1">
    <tr bgcolor="#9acd32">
      <th align="left">Paramater</th>
      <th align="left">Value</th>
    </tr>
    <xsl:for-each select="newtest">
    <tr>
      <td bgcolor="#9acd32">File size1: </td>
      <td><xsl:value-of select="filesize1"/></td>
    </tr>
    <tr>
      <td bgcolor="#9acd32">File size2: </td>
      <td><xsl:value-of select="filesize2"/></td>
    </tr>
    <tr>
      <td bgcolor="#9acd32">Result: </td>
      <td><xsl:value-of select="result"/></td>
    </tr>
    </xsl:for-each>
    </table>
  </body>
  </html>
</xsl:template>

</xsl:stylesheet>