#include <TestHarness.h>
#include <builder/Templater.h>

/////////////////////////////////////////////////////////////////////////////
TEST(Templater, simple_test)
{
  // Arrange
  Templater templater(Templater::PATH_ROOT_LAYOUT);

  // Act
  templater.setMacro(Templater::MACROS_CONTENT, "<p> C_O_N_T_E_N_T </p>");
  templater.setMacro(Templater::MACROS_HEADER,  "<p> H_E_A_D_E_R </p>");
  templater.setMacro(Templater::MACROS_FOOTER,  "<p> F_O_O_T_E_R </p>");

  // Assert
  ASSERT_TRUE(false == templater.generate().empty());
}
