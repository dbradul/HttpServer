/*******************************************************************
 * ContentReader.h
 *
 *  @date: 13-8-2014
 *  @author: DB
 ******************************************************************/

#ifndef CONTENTREADER_H_
#define CONTENTREADER_H_



class ContentReader
//---------------------------------------------------------------------------------------
{
   public:
      template<typename T>
      std::vector<T> getContent(std::string URL);
};

//---------------------------------------------------------------------------------------
template<>
std::vector<std::string> ContentReader::getContent(std::string URL)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "URL='%s'", URL.c_str());

   std::string fileContent;
   std::vector<std::string> entries;

   ////fileContent = Utils::getTextFileContent((workingDir + filePath).c_str());
   if (Utils::readAndCheckIfItIsBinary(URL.c_str(), fileContent))
   {
      entries.push_back("(binary content)");
   }

   else
   {
      Utils::split(entries, fileContent, "\r\n");
   }

   TRC_DEBUG_FUNC_EXIT(0U);

   return entries;
}

//---------------------------------------------------------------------------------------
template<>
std::vector<File> ContentReader::getContent(std::string URL)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "URL='%s'", URL.c_str());

   std::vector<File> flist;

   Utils::readDir(URL, flist);

   std::sort(flist.begin(), flist.end());

   TRC_DEBUG_FUNC_EXIT(0U);

   return flist;
}

#endif /* CONTENTREADER_H_ */
