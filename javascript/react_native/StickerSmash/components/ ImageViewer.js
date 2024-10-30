import { Image, View } from "react-native";
import { StyleSheet } from "react-native-web";

const PlaceholderImg = require('../assets/images/background-image.png');

export function ImageViewer() {
    return (
        <View style={styles.imageContainer}>
            <Image source={PlaceholderImg} style={styles.image} />
        </View>
    )
}

const styles = StyleSheet.create({
    imageContainer: {
      flex: 1,
      paddingTop: 58,
    },
    image: {
      width: 320,
      height: 440,
      borderRadius: 18,
    },
  });
  