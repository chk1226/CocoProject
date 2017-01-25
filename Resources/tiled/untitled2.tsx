<?xml version="1.0" encoding="UTF-8"?>
<tileset name="core" tilewidth="64" tileheight="64" spacing="1" margin="1" tilecount="9" columns="3">
 <properties>
  <property name="collision" type="bool" value="true"/>
 </properties>
 <image source="../core.png" width="256" height="256"/>
 <terraintypes>
  <terrain name="floor" tile="7">
   <properties>
    <property name="collision" type="bool" value="true"/>
    <property name="tile_name" value="tileBlue_05"/>
   </properties>
  </terrain>
  <terrain name="inside" tile="8">
   <properties>
    <property name="tile_name" value="tileBlue_03"/>
   </properties>
  </terrain>
 </terraintypes>
 <tile id="7" terrain="0,0,0,0"/>
 <tile id="8" terrain="1,1,1,1"/>
</tileset>
