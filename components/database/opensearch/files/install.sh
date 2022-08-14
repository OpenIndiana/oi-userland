#!/bin/bash
cd $DIR/build/distribution/local/opensearch-$COMPONENT_VERSION-SNAPSHOT
mkdir -p $PROTO_DIR/usr/share/opensearch
mkdir -p $PROTO_DIR/etc/opensearch
mkdir -p $PROTO_DIR/usr/bin
cp -r ./* $PROTO_DIR/usr/share/opensearch
mv $PROTO_DIR/usr/share/opensearch/config/* $PROTO_DIR/etc/opensearch
rmdir $PROTO_DIR/usr/share/opensearch/config
ln -s ../../../etc/opensearch $PROTO_DIR/usr/share/opensearch/config
ln -s ../share/opensearch/bin/opensearch $PROTO_DIR/usr/bin/opensearch
ln -s ../share/opensearch/bin/opensearch-keystore $PROTO_DIR/usr/bin/opensearch-keystore
ln -s ../share/opensearch/bin/opensearch-node $PROTO_DIR/usr/bin/opensearch-node
ln -s ../share/opensearch/bin/opensearch-plugin $PROTO_DIR/usr/bin/opensearch-plugin
ln -s ../share/opensearch/bin/opensearch-shard $PROTO_DIR/usr/bin/opensearch-shard
ln -s ../share/opensearch/bin/opensearch-upgrade $PROTO_DIR/usr/bin/opensearch-upgrade
sed 's|"`dirname "$0"`"|/usr/share/opensearch/bin|' -i "$PROTO_DIR/usr/share/opensearch/bin/opensearch"
sed 's|"`dirname "$0"`"|/usr/share/opensearch/bin|' -i "$PROTO_DIR/usr/share/opensearch/bin/opensearch-keystore"
sed 's|"`dirname "$0"`"|/usr/share/opensearch/bin|' -i "$PROTO_DIR/usr/share/opensearch/bin/opensearch-node"
sed 's|"`dirname "$0"`"|/usr/share/opensearch/bin|' -i "$PROTO_DIR/usr/share/opensearch/bin/opensearch-plugin"
sed 's|"`dirname "$0"`"|/usr/share/opensearch/bin|' -i "$PROTO_DIR/usr/share/opensearch/bin/opensearch-shard"
sed 's|"`dirname "$0"`"|/usr/share/opensearch/bin|' -i "$PROTO_DIR/usr/share/opensearch/bin/opensearch-upgrade"