#ifndef _DB_LUT_H_
#define _DB_LUT_H_

#define LUT_TOP_INDEX 800
#define DB2LIN_M 20
#define DB2LIN_N 400
#define LIN2DB_M 80.8081
#define LIN2DB_N -8.08081
static const float dB2Lin_LUT[801] = { 0.1, 0.100577, 0.101158, 0.101742, 0.102329, 0.10292, 0.103514, 0.104112, 0.104713, 0.105317, 0.105925, 0.106537, 0.107152, 0.10777, 0.108393, 0.109018, 0.109648, 0.110281, 0.110917, 0.111558, 0.112202, 0.112849, 0.113501, 0.114156, 0.114815, 0.115478, 0.116145, 0.116815, 0.117489, 0.118168, 0.11885, 0.119536, 0.120226, 0.12092, 0.121618, 0.12232, 0.123026, 0.123737, 0.124451, 0.12517, 0.125892, 0.126619, 0.12735, 0.128085, 0.128824, 0.129568, 0.130316, 0.131068, 0.131825, 0.132586, 0.133352, 0.134121, 0.134896, 0.135674, 0.136458, 0.137245, 0.138038, 0.138835, 0.139636, 0.140442, 0.141253, 0.142068, 0.142889, 0.143714, 0.144543, 0.145378, 0.146217, 0.147061, 0.14791, 0.148764, 0.149623, 0.150486, 0.151355, 0.152229, 0.153108, 0.153992, 0.154881, 0.155775, 0.156674, 0.157579, 0.158488, 0.159403, 0.160323, 0.161249, 0.16218, 0.163116, 0.164058, 0.165005, 0.165958, 0.166916, 0.167879, 0.168848, 0.169823, 0.170804, 0.17179, 0.172781, 0.173779, 0.174782, 0.175791, 0.176806, 0.177827, 0.178853, 0.179886, 0.180924, 0.181969, 0.183019, 0.184076, 0.185139, 0.186208, 0.187283, 0.188364, 0.189451, 0.190545, 0.191645, 0.192751, 0.193864, 0.194983, 0.196109, 0.197241, 0.19838, 0.199525, 0.200677, 0.201835, 0.203001, 0.204173, 0.205351, 0.206537, 0.207729, 0.208928, 0.210135, 0.211348, 0.212568, 0.213795, 0.215029, 0.216271, 0.217519, 0.218775, 0.220038, 0.221308, 0.222586, 0.223871, 0.225163, 0.226463, 0.227771, 0.229085, 0.230408, 0.231738, 0.233076, 0.234422, 0.235775, 0.237136, 0.238505, 0.239882, 0.241267, 0.24266, 0.244061, 0.24547, 0.246887, 0.248312, 0.249746, 0.251187, 0.252637, 0.254096, 0.255563, 0.257038, 0.258522, 0.260015, 0.261516, 0.263025, 0.264544, 0.266071, 0.267607, 0.269152, 0.270706, 0.272269, 0.273841, 0.275422, 0.277012, 0.278611, 0.280219, 0.281837, 0.283464, 0.2851, 0.286746, 0.288402, 0.290067, 0.291741, 0.293426, 0.29512, 0.296823, 0.298537, 0.30026, 0.301994, 0.303737, 0.305491, 0.307254, 0.309028, 0.310812, 0.312607, 0.314411, 0.316226, 0.318052, 0.319888, 0.321735, 0.323592, 0.32546, 0.327339, 0.329229, 0.33113, 0.333041, 0.334964, 0.336898, 0.338843, 0.340799, 0.342766, 0.344745, 0.346735, 0.348737, 0.35075, 0.352775, 0.354812, 0.35686, 0.358921, 0.360993, 0.363077, 0.365173, 0.367281, 0.369401, 0.371534, 0.373679, 0.375836, 0.378006, 0.380188, 0.382383, 0.38459, 0.386811, 0.389044, 0.39129, 0.393549, 0.395821, 0.398106, 0.400404, 0.402716, 0.405041, 0.407379, 0.409731, 0.412096, 0.414475, 0.416868, 0.419275, 0.421695, 0.42413, 0.426578, 0.429041, 0.431518, 0.434009, 0.436514, 0.439034, 0.441569, 0.444118, 0.446682, 0.449261, 0.451855, 0.454463, 0.457087, 0.459726, 0.46238, 0.465049, 0.467734, 0.470434, 0.47315, 0.475881, 0.478629, 0.481392, 0.484171, 0.486966, 0.489777, 0.492605, 0.495449, 0.498309, 0.501186, 0.504079, 0.506989, 0.509916, 0.51286, 0.515821, 0.518799, 0.521794, 0.524806, 0.527836, 0.530883, 0.533948, 0.537031, 0.540131, 0.543249, 0.546385, 0.54954, 0.552712, 0.555903, 0.559112, 0.56234, 0.565587, 0.568852, 0.572136, 0.575439, 0.578761, 0.582102, 0.585463, 0.588842, 0.592242, 0.595661, 0.5991, 0.602558, 0.606037, 0.609536, 0.613055, 0.616594, 0.620154, 0.623734, 0.627335, 0.630956, 0.634599, 0.638262, 0.641947, 0.645653, 0.64938, 0.653129, 0.6569, 0.660692, 0.664506, 0.668343, 0.672201, 0.676082, 0.679985, 0.68391, 0.687859, 0.69183, 0.695824, 0.699841, 0.703881, 0.707944, 0.712031, 0.716142, 0.720276, 0.724435, 0.728617, 0.732823, 0.737054, 0.741309, 0.745588, 0.749893, 0.754222, 0.758576, 0.762955, 0.76736, 0.77179, 0.776246, 0.780727, 0.785234, 0.789767, 0.794327, 0.798912, 0.803525, 0.808163, 0.812829, 0.817521, 0.822241, 0.826988, 0.831762, 0.836564, 0.841393, 0.846251, 0.851136, 0.85605, 0.860992, 0.865963, 0.870962, 0.87599, 0.881047, 0.886133, 0.891249, 0.896394, 0.901569, 0.906774, 0.912009, 0.917274, 0.92257, 0.927896, 0.933252, 0.93864, 0.944059, 0.949509, 0.954991, 0.960504, 0.966049, 0.971626, 0.977235, 0.982877, 0.988551, 0.994258, 0.999998, 1.00577, 1.01158, 1.01742, 1.02329, 1.0292, 1.03514, 1.04112, 1.04713, 1.05317, 1.05925, 1.06537, 1.07152, 1.0777, 1.08392, 1.09018, 1.09648, 1.10281, 1.10917, 1.11558, 1.12202, 1.12849, 1.13501, 1.14156, 1.14815, 1.15478, 1.16145, 1.16815, 1.1749, 1.18168, 1.1885, 1.19536, 1.20226, 1.2092, 1.21618, 1.2232, 1.23027, 1.23737, 1.24451, 1.2517, 1.25892, 1.26619, 1.2735, 1.28085, 1.28825, 1.29568, 1.30316, 1.31069, 1.31825, 1.32586, 1.33352, 1.34122, 1.34896, 1.35675, 1.36458, 1.37246, 1.38038, 1.38835, 1.39637, 1.40443, 1.41253, 1.42069, 1.42889, 1.43714, 1.44544, 1.45378, 1.46217, 1.47062, 1.4791, 1.48764, 1.49623, 1.50487, 1.51356, 1.5223, 1.53108, 1.53992, 1.54881, 1.55775, 1.56675, 1.57579, 1.58489, 1.59404, 1.60324, 1.6125, 1.62181, 1.63117, 1.64059, 1.65006, 1.65958, 1.66916, 1.6788, 1.68849, 1.69824, 1.70804, 1.7179, 1.72782, 1.7378, 1.74783, 1.75792, 1.76807, 1.77828, 1.78854, 1.79887, 1.80925, 1.8197, 1.8302, 1.84077, 1.8514, 1.86208, 1.87283, 1.88365, 1.89452, 1.90546, 1.91646, 1.92752, 1.93865, 1.94984, 1.9611, 1.97242, 1.98381, 1.99526, 2.00678, 2.01836, 2.03002, 2.04174, 2.05352, 2.06538, 2.0773, 2.08929, 2.10136, 2.11349, 2.12569, 2.13796, 2.1503, 2.16272, 2.1752, 2.18776, 2.20039, 2.21309, 2.22587, 2.23872, 2.25164, 2.26464, 2.27772, 2.29087, 2.30409, 2.31739, 2.33077, 2.34423, 2.35776, 2.37137, 2.38506, 2.39883, 2.41268, 2.42661, 2.44062, 2.45471, 2.46888, 2.48313, 2.49747, 2.51188, 2.52639, 2.54097, 2.55564, 2.57039, 2.58523, 2.60016, 2.61517, 2.63027, 2.64545, 2.66072, 2.67608, 2.69153, 2.70707, 2.7227, 2.73842, 2.75423, 2.77013, 2.78612, 2.8022, 2.81838, 2.83465, 2.85102, 2.86748, 2.88403, 2.90068, 2.91743, 2.93427, 2.95121, 2.96825, 2.98538, 3.00262, 3.01995, 3.03739, 3.05492, 3.07256, 3.0903, 3.10814, 3.12608, 3.14413, 3.16228, 3.18053, 3.1989, 3.21736, 3.23594, 3.25462, 3.27341, 3.29231, 3.31131, 3.33043, 3.34966, 3.36899, 3.38844, 3.408, 3.42768, 3.44747, 3.46737, 3.48739, 3.50752, 3.52777, 3.54814, 3.56862, 3.58922, 3.60994, 3.63078, 3.65174, 3.67283, 3.69403, 3.71536, 3.7368, 3.75838, 3.78007, 3.8019, 3.82385, 3.84592, 3.86812, 3.89046, 3.91292, 3.9355, 3.95822, 3.98108, 4.00406, 4.02717, 4.05042, 4.07381, 4.09733, 4.12098, 4.14477, 4.1687, 4.19277, 4.21697, 4.24132, 4.2658, 4.29043, 4.3152, 4.34011, 4.36516, 4.39037, 4.41571, 4.4412, 4.46684, 4.49263, 4.51857, 4.54465, 4.57089, 4.59728, 4.62382, 4.65051, 4.67736, 4.70436, 4.73152, 4.75884, 4.78631, 4.81394, 4.84173, 4.86968, 4.8978, 4.92607, 4.95451, 4.98311, 5.01188, 5.04082, 5.06992, 5.09919, 5.12862, 5.15823, 5.18801, 5.21796, 5.24809, 5.27838, 5.30886, 5.3395, 5.37033, 5.40133, 5.43252, 5.46388, 5.49542, 5.52715, 5.55906, 5.59115, 5.62343, 5.65589, 5.68854, 5.72138, 5.75441, 5.78763, 5.82105, 5.85465, 5.88845, 5.92245, 5.95664, 5.99103, 6.02561, 6.0604, 6.09539, 6.13058, 6.16597, 6.20156, 6.23737, 6.27337, 6.30959, 6.34602, 6.38265, 6.4195, 6.45656, 6.49383, 6.53132, 6.56903, 6.60695, 6.64509, 6.68345, 6.72204, 6.76084, 6.79987, 6.83913, 6.87861, 6.91832, 6.95826, 6.99843, 7.03883, 7.07947, 7.12034, 7.16144, 7.20278, 7.24436, 7.28619, 7.32825, 7.37055, 7.41311, 7.4559, 7.49894, 7.54223, 7.58578, 7.62957, 7.67361, 7.71791, 7.76247, 7.80728, 7.85235, 7.89768, 7.94328, 7.98913, 8.03525, 8.08164, 8.1283, 8.17522, 8.22242, 8.26988, 8.31763, 8.36564, 8.41394, 8.46251, 8.51137, 8.5605, 8.60992, 8.65963, 8.70962, 8.7599, 8.81047, 8.86133, 8.91249, 8.96394, 9.01569, 9.06774, 9.12008, 9.17273, 9.22569, 9.27895, 9.33251, 9.38639, 9.44058, 9.49508, 9.54989, 9.60502, 9.66047, 9.71624, 9.77233, 9.82875, 9.88549, 9.94256, 9.99996};
static const float Lin2dB_LUT[801] = { -20, -18.9878, -18.0813, -17.2606, -16.5108, -15.8206, -15.1812, -14.5856, -14.0283, -13.5046, -13.0107, -12.5434, -12.1, -11.678, -11.2757, -10.8911, -10.5229, -10.1696, -9.83016, -9.50347, -9.18863, -8.8848, -8.59124, -8.30728, -8.0323, -7.76577, -7.50717, -7.25605, -7.01199, -6.77459, -6.54352, -6.31843, -6.09903, -5.88503, -5.67618, -5.47223, -5.27296, -5.07816, -4.88764, -4.7012, -4.51868, -4.33992, -4.16477, -3.99307, -3.8247, -3.65954, -3.49746, -3.33834, -3.18209, -3.0286, -2.87778, -2.72953, -2.58377, -2.44041, -2.29938, -2.16061, -2.02401, -1.88954, -1.75711, -1.62667, -1.49816, -1.37152, -1.24671, -1.12366, -1.00233, -0.882675, -0.764644, -0.648195, -0.533287, -0.419879, -0.307933, -0.197411, -0.0882777, 0.0195013, 0.125959, 0.231127, 0.335037, 0.437719, 0.539201, 0.639512, 0.738677, 0.836722, 0.933673, 1.02955, 1.12439, 1.2182, 1.31101, 1.40283, 1.4937, 1.58362, 1.67263, 1.76073, 1.84794, 1.93429, 2.01979, 2.10446, 2.18831, 2.27135, 2.35361, 2.4351, 2.51583, 2.59582, 2.67508, 2.75362, 2.83145, 2.9086, 2.98507, 3.06087, 3.13601, 3.21051, 3.28437, 3.35762, 3.43025, 3.50228, 3.57371, 3.64456, 3.71484, 3.78456, 3.85372, 3.92233, 3.99041, 4.05796, 4.12498, 4.19149, 4.2575, 4.32301, 4.38803, 4.45256, 4.51662, 4.58021, 4.64334, 4.70602, 4.76824, 4.83002, 4.89137, 4.95228, 5.01277, 5.07284, 5.1325, 5.19176, 5.25061, 5.30906, 5.36713, 5.42481, 5.4821, 5.53903, 5.59558, 5.65177, 5.70759, 5.76306, 5.81818, 5.87295, 5.92737, 5.98146, 6.03521, 6.08863, 6.14173, 6.1945, 6.24696, 6.2991, 6.35092, 6.40245, 6.45366, 6.50458, 6.5552, 6.60553, 6.65556, 6.70531, 6.75478, 6.80397, 6.85288, 6.90151, 6.94988, 6.99798, 7.04581, 7.09338, 7.14069, 7.18775, 7.23455, 7.2811, 7.3274, 7.37346, 7.41927, 7.46485, 7.51018, 7.55528, 7.60015, 7.64479, 7.6892, 7.73338, 7.77734, 7.82108, 7.8646, 7.9079, 7.95099, 7.99386, 8.03652, 8.07898, 8.12123, 8.16327, 8.20511, 8.24676, 8.2882, 8.32944, 8.37049, 8.41135, 8.45202, 8.49249, 8.53278, 8.57289, 8.61281, 8.65254, 8.6921, 8.73147, 8.77067, 8.80969, 8.84854, 8.88721, 8.92572, 8.96405, 9.00222, 9.04021, 9.07805, 9.11571, 9.15322, 9.19056, 9.22775, 9.26477, 9.30164, 9.33836, 9.37492, 9.41132, 9.44757, 9.48368, 9.51963, 9.55543, 9.59109, 9.6266, 9.66197, 9.6972, 9.73228, 9.76722, 9.80202, 9.83668, 9.8712, 9.90559, 9.93984, 9.97396, 10.0079, 10.0418, 10.0755, 10.1091, 10.1426, 10.1759, 10.2091, 10.2422, 10.2751, 10.308, 10.3407, 10.3732, 10.4057, 10.438, 10.4703, 10.5024, 10.5343, 10.5662, 10.598, 10.6296, 10.6611, 10.6925, 10.7238, 10.755, 10.786, 10.817, 10.8478, 10.8786, 10.9092, 10.9397, 10.9701, 11.0005, 11.0307, 11.0608, 11.0907, 11.1206, 11.1504, 11.1801, 11.2097, 11.2392, 11.2686, 11.2979, 11.327, 11.3561, 11.3851, 11.414, 11.4428, 11.4715, 11.5001, 11.5287, 11.5571, 11.5854, 11.6136, 11.6418, 11.6699, 11.6978, 11.7257, 11.7535, 11.7812, 11.8088, 11.8363, 11.8637, 11.8911, 11.9184, 11.9455, 11.9726, 11.9996, 12.0266, 12.0534, 12.0802, 12.1068, 12.1334, 12.16, 12.1864, 12.2127, 12.239, 12.2652, 12.2913, 12.3174, 12.3433, 12.3692, 12.395, 12.4207, 12.4464, 12.472, 12.4975, 12.5229, 12.5483, 12.5735, 12.5987, 12.6239, 12.6489, 12.6739, 12.6988, 12.7237, 12.7485, 12.7732, 12.7978, 12.8224, 12.8469, 12.8713, 12.8956, 12.9199, 12.9442, 12.9683, 12.9924, 13.0164, 13.0404, 13.0643, 13.0881, 13.1119, 13.1355, 13.1592, 13.1827, 13.2062, 13.2297, 13.2531, 13.2764, 13.2996, 13.3228, 13.3459, 13.369, 13.392, 13.4149, 13.4378, 13.4606, 13.4834, 13.5061, 13.5288, 13.5513, 13.5739, 13.5963, 13.6187, 13.6411, 13.6634, 13.6856, 13.7078, 13.7299, 13.752, 13.774, 13.796, 13.8179, 13.8397, 13.8615, 13.8832, 13.9049, 13.9266, 13.9481, 13.9697, 13.9911, 14.0125, 14.0339, 14.0552, 14.0765, 14.0977, 14.1188, 14.1399, 14.161, 14.182, 14.2029, 14.2238, 14.2447, 14.2655, 14.2862, 14.3069, 14.3276, 14.3482, 14.3688, 14.3893, 14.4097, 14.4301, 14.4505, 14.4708, 14.4911, 14.5113, 14.5315, 14.5516, 14.5717, 14.5917, 14.6117, 14.6316, 14.6515, 14.6714, 14.6912, 14.7109, 14.7306, 14.7503, 14.7699, 14.7895, 14.8091, 14.8285, 14.848, 14.8674, 14.8868, 14.9061, 14.9254, 14.9446, 14.9638, 14.9829, 15.002, 15.0211, 15.0401, 15.0591, 15.0781, 15.097, 15.1158, 15.1346, 15.1534, 15.1721, 15.1908, 15.2095, 15.2281, 15.2467, 15.2652, 15.2837, 15.3022, 15.3206, 15.339, 15.3573, 15.3756, 15.3939, 15.4121, 15.4303, 15.4484, 15.4665, 15.4846, 15.5027, 15.5207, 15.5386, 15.5565, 15.5744, 15.5923, 15.6101, 15.6279, 15.6456, 15.6633, 15.681, 15.6986, 15.7162, 15.7338, 15.7513, 15.7688, 15.7863, 15.8037, 15.8211, 15.8384, 15.8557, 15.873, 15.8903, 15.9075, 15.9247, 15.9418, 15.9589, 15.976, 15.993, 16.01, 16.027, 16.044, 16.0609, 16.0778, 16.0946, 16.1114, 16.1282, 16.145, 16.1617, 16.1784, 16.195, 16.2116, 16.2282, 16.2448, 16.2613, 16.2778, 16.2943, 16.3107, 16.3271, 16.3435, 16.3598, 16.3761, 16.3924, 16.4086, 16.4249, 16.441, 16.4572, 16.4733, 16.4894, 16.5055, 16.5215, 16.5375, 16.5535, 16.5695, 16.5854, 16.6013, 16.6171, 16.633, 16.6488, 16.6645, 16.6803, 16.696, 16.7117, 16.7274, 16.743, 16.7586, 16.7742, 16.7897, 16.8053, 16.8207, 16.8362, 16.8517, 16.8671, 16.8825, 16.8978, 16.9131, 16.9284, 16.9437, 16.959, 16.9742, 16.9894, 17.0046, 17.0197, 17.0348, 17.0499, 17.065, 17.08, 17.095, 17.11, 17.125, 17.1399, 17.1548, 17.1697, 17.1846, 17.1994, 17.2142, 17.229, 17.2437, 17.2585, 17.2732, 17.2879, 17.3025, 17.3171, 17.3318, 17.3463, 17.3609, 17.3754, 17.3899, 17.4044, 17.4189, 17.4333, 17.4477, 17.4621, 17.4765, 17.4908, 17.5052, 17.5195, 17.5337, 17.548, 17.5622, 17.5764, 17.5906, 17.6047, 17.6189, 17.633, 17.6471, 17.6611, 17.6752, 17.6892, 17.7032, 17.7172, 17.7311, 17.745, 17.7589, 17.7728, 17.7867, 17.8005, 17.8144, 17.8281, 17.8419, 17.8557, 17.8694, 17.8831, 17.8968, 17.9105, 17.9241, 17.9377, 17.9513, 17.9649, 17.9785, 17.992, 18.0055, 18.019, 18.0325, 18.046, 18.0594, 18.0728, 18.0862, 18.0996, 18.1129, 18.1262, 18.1396, 18.1528, 18.1661, 18.1794, 18.1926, 18.2058, 18.219, 18.2322, 18.2453, 18.2584, 18.2715, 18.2846, 18.2977, 18.3108, 18.3238, 18.3368, 18.3498, 18.3628, 18.3757, 18.3886, 18.4016, 18.4145, 18.4273, 18.4402, 18.453, 18.4658, 18.4786, 18.4914, 18.5042, 18.5169, 18.5297, 18.5424, 18.555, 18.5677, 18.5804, 18.593, 18.6056, 18.6182, 18.6308, 18.6433, 18.6559, 18.6684, 18.6809, 18.6934, 18.7059, 18.7183, 18.7308, 18.7432, 18.7556, 18.768, 18.7803, 18.7927, 18.805, 18.8173, 18.8296, 18.8419, 18.8541, 18.8664, 18.8786, 18.8908, 18.903, 18.9152, 18.9273, 18.9394, 18.9516, 18.9637, 18.9758, 18.9878, 18.9999, 19.0119, 19.0239, 19.0359, 19.0479, 19.0599, 19.0719, 19.0838, 19.0957, 19.1076, 19.1195, 19.1314, 19.1432, 19.1551, 19.1669, 19.1787, 19.1905, 19.2023, 19.214, 19.2258, 19.2375, 19.2492, 19.2609, 19.2726, 19.2843, 19.2959, 19.3076, 19.3192, 19.3308, 19.3424, 19.3539, 19.3655, 19.377, 19.3886, 19.4001, 19.4116, 19.423, 19.4345, 19.446, 19.4574, 19.4688, 19.4802, 19.4916, 19.503, 19.5143, 19.5257, 19.537, 19.5483, 19.5596, 19.5709, 19.5822, 19.5935, 19.6047, 19.6159, 19.6271, 19.6383, 19.6495, 19.6607, 19.6719, 19.683, 19.6941, 19.7052, 19.7163, 19.7274, 19.7385, 19.7495, 19.7606, 19.7716, 19.7826, 19.7936, 19.8046, 19.8156, 19.8265, 19.8375, 19.8484, 19.8593, 19.8702, 19.8811, 19.892, 19.9029, 19.9137, 19.9246, 19.9354, 19.9462, 19.957, 19.9678, 19.9785, 19.9893};

#endif